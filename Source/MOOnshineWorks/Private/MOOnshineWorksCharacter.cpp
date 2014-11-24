// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Pickup.h"
#include "Door.h"
#include "MOOnshineWorksGameMode.h"

//////////////////////////////////////////////////////////////////////////
// AMOOnshineWorksCharacter

AMOOnshineWorksCharacter::AMOOnshineWorksCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    //set base health
    BaseHealth = 100.f;
    //set base mana
    BaseMana = 0.f;
	//set currentHealth at 3
	CurrentHealth = BaseHealth;
	//set CurrentMana at 0
	CurrentMana = BaseMana;
	//set SpeedFactor
	SpeedFactor = 0.75f;
	//set BaseSpeed
	BaseSpeed = 10.0f;
    //set BaseStamina
    BaseStamina = 150.0f;
    //Set stamina
    Stamina = BaseStamina;
    //Sprint toggle
    IsSprinting = false;
    //Aim toggle
    IsAiming = false;
    //Move forward state
    IsMovingForward = false;
    
    //Set camera values
    baseCameraZoom = 250;
    baseCameraAimZoom = 150;
    baseCameraSprintZoom = 160;
    baseCameraOffset = FVector(7.5f, 90.0f, 25.0f);
    baseZoomOffset = FVector(15.0f, 90.0f, 25.0f);
    baseSprintOffset = FVector(0.0f, 0.0f, 20.0f);
    
	// Create our battery collection volume.
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// setup light
	DimSpeed = 0.05f;
	MaxRadius = 2000.f;
	LightPercentage = 1.0f;

	Light = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "Light");
	Light->SetIntensity(5.f);
	Light->SetAttenuationRadius(MaxRadius);
	Light->SetSourceRadius(1.f);
	Light->bUseInverseSquaredFalloff = false;
	Light->SetLightFalloffExponent(2.0f);
	Light->MinRoughness = 0.001f;
	Light->SetCastShadows(false);
	Light->AttachTo(RootComponent);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = baseCameraZoom; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AMOOnshineWorksCharacter::ReceiveBeginPlay()
{
	UWorld* const world = GetWorld();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("making gun"));
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.bNoCollisionFail = false;

		activeItem = world->SpawnActor<AGun>(TSubclassOf<AGun>(*(BlueprintLoader::Get().GetBP(FName("PistolClass")))), spawnParams);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("gun made, yay!"));
		activeItem->SetActorLocation(RootComponent->GetSocketLocation("head"), false);
		activeItem->SetActorRotation(FRotator::ZeroRotator);
		activeItem->AttachRootComponentToActor(this, "head");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("gun attached"));
	}
    CameraBoom->SocketOffset = baseCameraOffset;
    
	Super::ReceiveBeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMOOnshineWorksCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMOOnshineWorksCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMOOnshineWorksCharacter::StopJumping);
	//InputComponent->BindAction("CollectPickups", IE_Released, this, &AMOOnshineWorksCharacter::CollectItems);
    InputComponent->BindAction("Sprint", IE_Pressed, this, &AMOOnshineWorksCharacter::StartSprint);
    InputComponent->BindAction("Sprint", IE_Released, this, &AMOOnshineWorksCharacter::EndSprint);
	InputComponent->BindAction("Use", IE_Pressed, this, &AMOOnshineWorksCharacter::StartUse);
	InputComponent->BindAction("Use", IE_Released, this, &AMOOnshineWorksCharacter::EndUse);
    InputComponent->BindAction("Aim", IE_Pressed, this, &AMOOnshineWorksCharacter::StartAim);
    InputComponent->BindAction("Aim", IE_Released, this, &AMOOnshineWorksCharacter::EndAim);
	InputComponent->BindAction("reload", IE_Pressed, this, &AMOOnshineWorksCharacter::reload);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMOOnshineWorksCharacter::Interact);
    
	InputComponent->BindAxis("MoveForward", this, &AMOOnshineWorksCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMOOnshineWorksCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMOOnshineWorksCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMOOnshineWorksCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AMOOnshineWorksCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMOOnshineWorksCharacter::TouchStopped);
}


void AMOOnshineWorksCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AMOOnshineWorksCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AMOOnshineWorksCharacter::StartUse()
{
	if (activeItem)
	{
		activeItem->Use();
	}
}

void AMOOnshineWorksCharacter::EndUse()
{

}

void AMOOnshineWorksCharacter::StartAim()
{
    if(IsSprinting == true){
        EndSprint();
    }
    CameraBoom->TargetArmLength = baseCameraAimZoom;
    CameraBoom->SocketOffset = baseZoomOffset;
    IsAiming = true;
}

void AMOOnshineWorksCharacter::EndAim()
{
    CameraBoom->TargetArmLength = baseCameraZoom;
    CameraBoom->SocketOffset = baseCameraOffset;
    IsAiming = false;
}

void AMOOnshineWorksCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMOOnshineWorksCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMOOnshineWorksCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
        IsMovingForward = true;
    }else{
        IsMovingForward = false;
    }
}

void AMOOnshineWorksCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMOOnshineWorksCharacter::StartSprint()
{
    if(Stamina > 0 && IsMovingForward == true)
    {
        //Adjust camera to sprint values
        CameraBoom->TargetArmLength = baseCameraSprintZoom;
        CameraBoom->SocketOffset = baseSprintOffset;
        //PerformCameraShake();
        //Adjust movement speed to sprint values & switch boolean to true
        CharacterMovement->MaxWalkSpeed *= 1.75;
        IsSprinting = true;
    }
}

void AMOOnshineWorksCharacter::EndSprint()
{
    //If statement Assures that no double adjustment of speed is called in some situations
    if(IsSprinting == true)
    {
        //Adjust camera to standard values
        CameraBoom->TargetArmLength = baseCameraZoom;
        CameraBoom->SocketOffset = baseCameraOffset;
        
        //Adjust movement speed to standard values & switch boolean to false
        CharacterMovement->MaxWalkSpeed /= 7;
        CharacterMovement->MaxWalkSpeed *= 4;
        IsSprinting = false;
    }
}

void AMOOnshineWorksCharacter::CollectItems()
{

	// Get all overlapping Actors and store them in a CollectedActors array.
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// For each Actor collected

	for (AActor* Item : CollectedActors)
	{
		APickup* Pickup = Cast<APickup>(Item);
		ADoor* Door = Cast<ADoor>(Item);
		if (Pickup)
		{
			Pickup->OnPickedUp(this);
		}
	}
}

void AMOOnshineWorksCharacter::Interact()
{
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// For each Actor collected

	for (AActor* Item : CollectedActors)
	{
		ADoor* Door = Cast<ADoor>(Item);
		if (Door) {
			Door->DoorOpen();
		}
	}
}

void AMOOnshineWorksCharacter::equipPistol()
{
	if (activeItem)
	{
		//activeItem->GetRootComponent()->AttachTo(RootComponent);
		//Mesh->GetSocketByName("hand_rSocket")->AttachActor(activeItem, Mesh);
		activeItem->GetRootComponent()->AttachParent = Mesh;
		activeItem->GetRootComponent()->AttachSocketName = FName(TEXT("hand_rSocket"));
		/*activeItem->SetActorLocation(Mesh->GetSocketLocation("hand_rSocket"), false);
		activeItem->SetActorRotation(FRotator::ZeroRotator);
		activeItem->AttachRootComponentTo(this->Mesh, "hand_rSocket");*/
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("gun attached"));
	}
}
/*
void AMOOnshineWorksCharacter::useActiveItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("getting into activating"));
	if (activeItem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("activating"));
		activeItem->activate(GetControlRotation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not activating"));
	}
} */

void AMOOnshineWorksCharacter::reload()
{
	/*if (&activeItem != NULL)
	{
		AGun* gun = Cast<AGun>(activeItem);
		if (gun)
		{
			gun->reload();
		}
	}*/
}

void AMOOnshineWorksCharacter::CalcStamina()
{
    if(IsSprinting == true && Stamina > 0.f)
    {
        Stamina = Stamina - 1.f;
    }
    else if(IsSprinting == false && Stamina < 150.0f)
    {
        Stamina = Stamina + 0.5f;
    }
    
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Stamina is " + FString::FromInt(Stamina)));
    if(Stamina > 150.f)
    {
        Stamina = 150.f;
    }
}

void AMOOnshineWorksCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LightPercentage > 0){
		LightPercentage -= DimSpeed * LightPercentage * DeltaSeconds;
	}
	else{
		LightPercentage = 0;
	}
	
	UpdateLightRadius(DeltaSeconds);
    
    CalcStamina();
	CollectItems();


    if(Stamina < 1)
    {
        EndSprint();
    }
    //CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;
}

/* Character health logic */
void AMOOnshineWorksCharacter::SetBaseHealth(float NewBaseHealth) { BaseHealth = NewBaseHealth;  };
float AMOOnshineWorksCharacter::GetBaseHealth() { return BaseHealth; };
void AMOOnshineWorksCharacter::SetCurrentHealth(float NewCurrentHealth) {
	CurrentHealth = NewCurrentHealth; 
	if (CurrentHealth > BaseHealth){ CurrentHealth = BaseHealth; }
	else if (CurrentHealth > 0){ Destroy(); };
};
float AMOOnshineWorksCharacter::GetCurrentHealth(){ return CurrentHealth; };


/* Character light logic */
void AMOOnshineWorksCharacter::SetLightPercentage(float NewLightPercentage) { 
	LightPercentage = NewLightPercentage; if (LightPercentage > 1) LightPercentage = 1;
};
float AMOOnshineWorksCharacter::GetLightPercentage(){ return LightPercentage; };
void AMOOnshineWorksCharacter::SetDimSpeed(float NewDimSpeed) { DimSpeed = NewDimSpeed; };
float AMOOnshineWorksCharacter::GetDimSpeed(){ return DimSpeed; };
void AMOOnshineWorksCharacter::SetMaxRadius(float NewMaxRadius) { MaxRadius = NewMaxRadius; };
float AMOOnshineWorksCharacter::GetMaxRadius(){ return MaxRadius; };

void AMOOnshineWorksCharacter::UpdateLightRadius(float DeltaSeconds)
{
	float ATRadius = GetMaxRadius() * GetLightPercentage();
	Light->SetAttenuationRadius(ATRadius);
}

void AMOOnshineWorksCharacter::DealDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth < 0)
	{
		Destroy();
	}
}

/* Character Stamina logic  */
void AMOOnshineWorksCharacter::SetBaseStamina(float NewBastStamina) { BaseStamina = NewBastStamina; };
float AMOOnshineWorksCharacter::GetBaseStamina(){ return BaseStamina; };
void AMOOnshineWorksCharacter::SetStamina(float New_Stamina) { 
	Stamina = New_Stamina; if (Stamina > BaseStamina) Stamina = BaseStamina;
};
float AMOOnshineWorksCharacter::GetStamina() { return Stamina; };

/* this function needs to be reviewed, doesn't work somehow
 void AMOOnshineWorksCharacter::PerformCameraShake()
 {
 UCameraShake* CameraShake = ConstructObject<UCameraShake>(UCameraShake::StaticClass());
 CameraShake->OscillationDuration = -1.0f; //negative value will run forever
 CameraShake->RotOscillation.Pitch.Amplitude = 1.0f;
 CameraShake->RotOscillation.Pitch.Frequency = 0.5f;
 CameraShake->RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
 CameraShake->RotOscillation.Yaw.Amplitude = 1.0f;
 CameraShake->RotOscillation.Yaw.Frequency = 0.5f;
 CameraShake->RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
 CameraShake->FOVOscillation.Amplitude = 1.0f;
 
 //Somehow doesn't do anything... should work though. Figure out later.
 GetWorld()->GetFirstLocalPlayerFromController()->PlayerController->ClientPlayCameraShake(CameraShake->GetClass(), 1.0f);
 }*/
