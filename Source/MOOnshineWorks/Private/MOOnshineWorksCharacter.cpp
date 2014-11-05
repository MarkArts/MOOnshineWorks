// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "ChestPickup.h"

//////////////////////////////////////////////////////////////////////////
// AMOOnshineWorksCharacter

AMOOnshineWorksCharacter::AMOOnshineWorksCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//set CurrentMana at 0
	CurrentMana = 0.f;
	//set SpeedFactor
	SpeedFactor = 0.75f;
	//set BaseSpeed
	BaseSpeed = 10.0f;
    //Sprint toggle
    IsSprinting = false;
    //Aim toggle
    IsAiming = false;

	// Create our battery collection volume.
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);



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
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
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
    CameraBoom->TargetArmLength = 175.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 0.0f);
}

void AMOOnshineWorksCharacter::EndAim()
{
    CameraBoom->TargetArmLength = 250.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
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
    //CharacterMovement->MaxWalkSpeed = 2000.0f;
    //CharacterMovement->MaxWalkSpeed = (SpeedFactor * PowerLevel + BaseSpeed)*2;
    // CameraBoom->TargetArmLength = 175.0f;
    // CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 0.0f);
    
    CharacterMovement->MaxWalkSpeed *= 1.5;
    IsSprinting = true;
}

void AMOOnshineWorksCharacter::EndSprint()
{
    //CharacterMovement->MaxWalkSpeed = 1000.0f;
    //CharacterMovement->MaxWalkSpeed = (SpeedFactor * PowerLevel + BaseSpeed)/2;
    //  CameraBoom->TargetArmLength = 150.0f;
    //  CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 50.0f);
    
    CharacterMovement->MaxWalkSpeed /= 3;
    CharacterMovement->MaxWalkSpeed *= 2;
    IsSprinting = false;
}

void AMOOnshineWorksCharacter::CollectItems()
{
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

/*
void AMOOnshineWorksCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;
}
*/