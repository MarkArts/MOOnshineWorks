// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "MOOnshineWorksGameMode.h"
#include "Socket.h"
#include "ChestPickup.h"

//////////////////////////////////////////////////////////////////////////
// AMOOnshineWorksCharacter

AMOOnshineWorksCharacter::AMOOnshineWorksCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//set currentHealth at 3
	CurrentHealth = 1.f;
	//set CurrentMana at 0
	CurrentMana = 0.f;
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

    //Set camera values
    baseCameraZoom = 250;
    baseCameraAimZoom = 150;
    baseCameraSprintZoom = 160;
    baseCameraOffset = FVector(0.0f, 0.0f, 0.0f);
    baseZoomOffset = FVector(10.0f, 65.0f, 20.0f);
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
	bUseControllerRotationYaw = false;
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

//////////////////////////////////////////////////////////////////////////
// Input

void AMOOnshineWorksCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMOOnshineWorksCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMOOnshineWorksCharacter::StopJumping);
	InputComponent->BindAction("CollectPickups", IE_Released, this, &AMOOnshineWorksCharacter::CollectItems);
    InputComponent->BindAction("Sprint", IE_Pressed, this, &AMOOnshineWorksCharacter::StartSprint);
    InputComponent->BindAction("Sprint", IE_Released, this, &AMOOnshineWorksCharacter::EndSprint);
    InputComponent->BindAction("Aim", IE_Pressed, this, &AMOOnshineWorksCharacter::StartAim);
    InputComponent->BindAction("Aim", IE_Released, this, &AMOOnshineWorksCharacter::EndAim);
    
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
    if(Stamina > 0)
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

	AMOOnshineWorksGameMode* GameMode = (AMOOnshineWorksGameMode*)GetWorld()->GetAuthGameMode();
	(*GameMode).Socket->SendString(TEXT("Ik druk op E mon pere"));

	printf("CollectItems aangeroepen!");
	float ManaValue = 0.f;

	// Get all overlapping Actors and store them in a CollectedActors array.
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// For each Actor collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Try to Cast the collected Actor to AChestPickup.
		AChestPickup* const TestChest = Cast<AChestPickup>(CollectedActors[iCollected]);

		// If the cast is successful, and the chest is valid and active
		if (TestChest && !TestChest->IsPendingKill() && TestChest->bIsActive) //Check if you picked up a chest!
		{
			// Store its battery power for adding to the character's power.
			ManaValue = ManaValue + TestChest->valueMana;
			// Deactivate the battery
			TestChest->bIsActive = false;
			// Call the Chest's OnPickedUp function so destroy
			TestChest->OnPickedUp();
			printf("kom ik hier!");
		}
	}

	if (ManaValue > 0.f)
	{
		// Call the !Blueprinted implementation! of ManaUp with the total mana as input.
		ManaUp(ManaValue);
	}
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

	LightPercentage -= DimSpeed * LightPercentage * DeltaSeconds;
	UpdateLightRadius(DeltaSeconds);
    
    CalcStamina();
    
    if(Stamina < 1)
    {
        EndSprint();
    }
    //CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;
}

void AMOOnshineWorksCharacter::UpdateLightRadius(float DeltaSeconds)
{
	float ATRadius = MaxRadius * LightPercentage;
	Light->SetAttenuationRadius(ATRadius);
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
