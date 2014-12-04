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
	/** Make Character able to produce sound */
	NoiseEmitter = PCIP.CreateDefaultSubobject<UPawnNoiseEmitterComponent>(this, TEXT("Noise Emitter"));

    //set base health
    BaseHealth = 100.f;
    //set base mana
    BaseMana = 0.f;
	//set currentHealth at 3
	CurrentHealth = BaseHealth;
	//set CurrentMana at 0
	CurrentMana = BaseMana;
    //set BaseStamina
    BaseStamina = 150.0f;
    //Set stamina
    Stamina = BaseStamina;
    //Sprint toggle
    IsSprinting = false;
    //Set sprint multiplier;
    SprintMultiplier = 1.75;
    //Aim toggle
    IsAiming = false;
	//AI starts Dark
	DarkLight = true;
    //Move forward state
    IsMovingForward = false;
    
    //Set camera values
    baseCameraZoom = 250;
    baseCameraAimZoom = 150;
    baseCameraSprintZoom = 160;
    baseCameraOffset = FVector(7.5f, 100.0f, 25.0f);
    baseZoomOffset = FVector(17.5f, 90.0f, 25.0f);
    baseSprintOffset = FVector(10.0f, 90.0f, 25.0f);
    
	// Create our battery collection volume.
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// setup light
	LightDimSpeed = 0.05f;
	LightMaxRadius = 2000.f;
	LightMinRadius = 200.f;
	LightPercentage = 1.0f;

	Light = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "Light");
	Light->SetIntensity(5.f);
	Light->SetAttenuationRadius(LightMaxRadius);
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
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachParent = CapsuleComponent;
	FollowCamera->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FollowCamera->bUsePawnControlRotation = true;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
    
    //Set avatar img
    // Set the standard texture
    static ConstructorHelpers::FObjectFinder<UTexture2D> StandardAvatarTexObj(TEXT("Texture2D'/Game/Blueprints/HUDBlueprints/Normal.Normal'"));
    StandardAvatar = StandardAvatarTexObj.Object;
    static ConstructorHelpers::FObjectFinder<UTexture2D> LowHPAvatarTexObj(TEXT("Texture2D'/Game/Blueprints/HUDBlueprints/Hurt.Hurt'"));
    AvatarLowHP = LowHPAvatarTexObj.Object;
    static ConstructorHelpers::FObjectFinder<UTexture2D> VeryLowHPAvatarTexObj(TEXT("Texture2D'/Game/Blueprints/HUDBlueprints/Almost-Dead.Almost-Dead'"));
    AvatarVeryLowHP = VeryLowHPAvatarTexObj.Object;
    

}

void AMOOnshineWorksCharacter::ReceiveBeginPlay()
{
	UWorld* const world = GetWorld();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("making gun"));
	if (world)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoCollisionFail = false;

		USceneComponent *Mesh = nullptr;

		for(int i = 0; i < RootComponent->GetNumChildrenComponents(); i++)
		{
			USceneComponent* Comp =  RootComponent->GetChildComponent(i);

			if (Comp->GetName() == FString("CharacterMesh0"))
			{
				Mesh = Comp;
			}
		}
		AGun* Pistol = world->SpawnActor<AGun>(TSubclassOf<AGun>(*(BlueprintLoader::Get().GetBP(FName("PistolClass")))), SpawnParams);
		EquipGun(Pistol);
		activeItem = Pistol;
	}
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
	InputComponent->BindAction("Reload", IE_Pressed, this, &AMOOnshineWorksCharacter::Reload);
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
		if (!IsSprinting)
		{
			activeItem->Use();
		}
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
    IsAiming = true;
}

void AMOOnshineWorksCharacter::EndAim()
{
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
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMOOnshineWorksCharacter::StartSprint()
{
    if(Stamina > 0 && IsMovingForward == true)
    {
        //Adjust camera to sprint values
        //PerformCameraShake();
        //Adjust movement speed to sprint values & switch boolean to true
        CharacterMovement->MaxWalkSpeed *= SprintMultiplier;
        IsSprinting = true;
    }

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("MakeSound aangeroepen!"));
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
		if (playerCharacter)
		{
			FVector loc = playerCharacter->GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("MakeSound!"));
			MakeNoise(10.0f, playerCharacter, loc);
		}
	}
}

void AMOOnshineWorksCharacter::EndSprint()
{
    //If statement Assures that no double adjustment of speed is called in some situations
    if(IsSprinting == true)
    {
        //Adjust camera to standard values
        //Adjust movement speed to standard values & switch boolean to false
        CharacterMovement->MaxWalkSpeed = (CharacterMovement->MaxWalkSpeed / (SprintMultiplier * 100)) * 100;
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
		if (Item->GetClass()->IsChildOf(ADoor::StaticClass()))
		{	
			ADoor* Door = Cast<ADoor>(Item);
			if (Door) {
				Door->DoorOpen();
			}
		}
		if (Item->GetClass()->IsChildOf(AGun::StaticClass()))
		{
			AGun* Gun = Cast<AGun>(Item);
			if (Gun)
			{
				//add to inventory
			}
		}
	}
}

void AMOOnshineWorksCharacter::EquipGun(AGun* Gun)
{
	Gun->SetActorLocation(RootComponent->GetComponentLocation());
	Gun->SetActorRelativeLocation(FVector(25.f, 25.f, 50.f));
	Gun->AttachRootComponentTo(RootComponent);
	FRotator GunRotation = FRotator::ZeroRotator;
	GunRotation.Yaw = 75;
	GunRotation.Roll = 0;
	GunRotation.Pitch = 0;
	Gun->SetActorRotation(GunRotation);
	Gun->SetOwner(this);
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

void AMOOnshineWorksCharacter::Reload()
{
	if (activeItem)
	{
		APistol* Pistol = Cast<APistol>(activeItem);
		if (Pistol)
		{
			Pistol->Reload();
		}
	}
}

void AMOOnshineWorksCharacter::CalcStamina()
{
    if(IsSprinting == true && GetStamina() > 0.f)
    {
        SetStamina(GetStamina() - 1.f);
    }
    else if(IsSprinting == false && GetStamina() < GetBaseStamina())
    {
        SetStamina(GetStamina() + 0.5f);
    }
    
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Stamina is " + FString::FromInt(Stamina)));
    if(GetStamina() > GetBaseStamina())
    {
        SetStamina(GetBaseStamina());
    }
}

void AMOOnshineWorksCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateLightRadius(DeltaSeconds);
	SetLightRadius();

    CalcStamina();
	CollectItems();


    if(GetStamina() < 1)
    {
        EndSprint();
    }
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
float AMOOnshineWorksCharacter::GetCurrentMana(){ return CurrentMana; }


/* Character light logic */
void AMOOnshineWorksCharacter::SetLightPercentage(float NewLightPercentage) { 
	LightPercentage = NewLightPercentage; if (LightPercentage > 1) LightPercentage = 1;
};
float AMOOnshineWorksCharacter::GetLightPercentage(){ return LightPercentage; };
void AMOOnshineWorksCharacter::SetLightDimSpeed(float NewLightDimSpeed) { LightDimSpeed = NewLightDimSpeed; };
float AMOOnshineWorksCharacter::GetLightDimSpeed(){ return LightDimSpeed; };
void AMOOnshineWorksCharacter::SetLightMaxRadius(float NewLightMaxRadius) { LightMaxRadius = NewLightMaxRadius; };
float AMOOnshineWorksCharacter::GetLightMaxRadius(){ return LightMaxRadius; };
void AMOOnshineWorksCharacter::SetLightMinRadius(float NewLightMinRadius) { LightMinRadius = NewLightMinRadius; };
float AMOOnshineWorksCharacter::GetLightMinRadius(){ return LightMinRadius; };


void AMOOnshineWorksCharacter::UpdateLightRadius(float DeltaSeconds)
{
	if (LightPercentage > 0){
		LightPercentage -= LightDimSpeed * DeltaSeconds;
	}
	else{
		LightPercentage = 0;
	}
}

void AMOOnshineWorksCharacter::SetLightRadius()
{
	float ATRadius = ( GetLightMaxRadius() - GetLightMinRadius()) * GetLightPercentage() + GetLightMinRadius();
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
void AMOOnshineWorksCharacter::SetBaseStamina(float NewBaseStamina) { BaseStamina = NewBaseStamina; };
float AMOOnshineWorksCharacter::GetBaseStamina(){ return BaseStamina; };
void AMOOnshineWorksCharacter::SetStamina(float New_Stamina) { 
	Stamina = New_Stamina; if (Stamina > BaseStamina) Stamina = BaseStamina;
};
float AMOOnshineWorksCharacter::GetStamina() { return Stamina; };

UTexture2D* AMOOnshineWorksCharacter::GetAvatar()
{
    if(GetCurrentHealth() < (GetBaseHealth() / 4 )){
        return AvatarVeryLowHP;
    }
    else if(GetCurrentHealth() < (GetBaseHealth() / 2 )){
        return AvatarLowHP;
    }
    else{
        return StandardAvatar;
    }
}

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
