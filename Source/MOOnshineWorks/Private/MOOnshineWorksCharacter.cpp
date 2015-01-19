// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Door.h"
#include "DoorKey.h"
#include "KeyHolder.h"
#include "Interactable.h"
#include "Collectible.h"
#include "Helpers.h"
#include "Gun.h"
#include "BaseLevelScriptActor.h"
#include "Shotgun.h"
#include "DebuffManager.h"
#include "SlowDownDebuff.h"
#include "SuperJumpDebuff.h"
#include "MOOnshineWorksGameMode.h"

//////////////////////////////////////////////////////////////////////////
// AMOOnshineWorksCharacter

AMOOnshineWorksCharacter::AMOOnshineWorksCharacter(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/** Make Character able to produce sound */
	NoiseEmitter = PCIP.CreateDefaultSubobject<UPawnNoiseEmitterComponent>(this, TEXT("Noise Emitter"));

	DidHit = false;
	IsDeath = false;

	//set base WalkSpeed
	//CharacterMovement->MaxWalkSpeed = baseSpeed;

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
    //Set walkspeed
    CharacterWalkSpeed = 1000;
    //Aim toggle
    IsAiming = false;
	//AI starts Dark
	DarkLight = true;
    //Move forward state
    IsMovingForward = false;
	IsMovingSideway = false;
	bIdleCameraShake = false;
	bWalkCameraShake = false;
	bSprintCameraShake = false;
    
    //Set camera values
    baseCameraZoom = 250;
    baseCameraAimZoom = 150;
    baseCameraSprintZoom = 160;
    baseCameraOffset = FVector(7.5f, 100.0f, 25.0f);
    baseZoomOffset = FVector(17.5f, 90.0f, 25.0f);
    baseSprintOffset = FVector(10.0f, 90.0f, 25.0f);
    
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	InteractionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("InteractionSphere"));
	InteractionSphere->AttachTo(RootComponent);
	InteractionSphere->SetSphereRadius(150.f);

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
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Configure character movement
	//CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	//CharacterMovement->AirControl = 0.2f;

	// Create a follow camera
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

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

	kh = new KeyHolder();
	//debuffManager = new DebuffManager();
	
}

void AMOOnshineWorksCharacter::Respawn()
{

	//Reset();

	//FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	//AMOOnshineWorksCharacter* NewPlayer = GetWorld()->SpawnActor<AMOOnshineWorksCharacter>(this->StaticClass(), SpawnParameters);
	//NewPlayer->PossessedBy(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	((AMOOnshineWorksGameMode*)UGameplayStatics::GetGameMode(GetWorld()))->RestoreCheckpoint();
	//Destroy();
}

FPlayerSave AMOOnshineWorksCharacter::CreatePlayerSave()
{

	TArray<FName> Weapons;

	TArray<APlayerGun*> Guns = WeaponStrap->Guns;
	int8 WeaponsNum = Guns.Num();
	for (int8 I = 0; I < WeaponsNum; I++)
	{
		Weapons.Add(Guns[I]->Name);
	}

	return{
		GetTransform().GetLocation(),
		GetTransform().Rotator(),
		Weapons,
		AmmoContainer->AmmoCounters
	};
}

void AMOOnshineWorksCharacter::LoadPlayerSave(FPlayerSave PlayerSave)
{

	if (!Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Looks like your loading a level that doesn't support the save system."));
		return;
	}

	/* Set base vairables should peferably not need to happen but it seems like we have no other choice with the current code base */
	CurrentHealth = BaseHealth;
	CurrentMana = BaseMana;
	Stamina = BaseStamina;
	LightPercentage = 1.0f;

	SetActorTransform({
		PlayerSave.Rotation,
		PlayerSave.Position,
		FVector(1.f,1.f,1.f)
	});

	int8 WeaponsNum = PlayerSave.Weapons.Num();
	for (int8 I = 0; I < WeaponsNum; I++)
	{
		TSubclassOf<APlayerGun> Gun = TSubclassOf<APlayerGun>(*BlueprintLoader::Get().GetBP(PlayerSave.Weapons[I]));
		if (!WeaponStrap->ContainsGun(Gun))
		{
			EquipGun(GetWorld()->SpawnActor<APlayerGun>(Gun));
		}
	}


	if (PlayerSave.AmmoCounters.Num() > 0){
		AmmoContainer->AmmoCounters = PlayerSave.AmmoCounters;
	}

	IsDeath = false;
}

void AMOOnshineWorksCharacter::ReceiveBeginPlay()
{
	UWorld* const World = GetWorld();

	if (World)
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

	//	APlayerGun* Pistol = World->SpawnActor<APlayerGun>(TSubclassOf<APlayerGun>(*(BlueprintLoader::Get().GetBP(FName("Crossbow")))), SpawnParams);
		AmmoContainer = World->SpawnActor<AAmmoContainer>(AAmmoContainer::StaticClass(), SpawnParams);
		WeaponStrap = World->SpawnActor<AWeaponStrap>(AWeaponStrap::StaticClass(), SpawnParams);
		//EquipGun(Pistol);
		GetCharacterMovement()->MaxWalkSpeed = CharacterWalkSpeed;

		LoadPlayerSave(UHelpers::GetSaveManager(World)->GetData()->Player);
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
	InputComponent->BindAction("CollectPickups", IE_Released, this, &AMOOnshineWorksCharacter::CollectItems);
    InputComponent->BindAction("Sprint", IE_Pressed, this, &AMOOnshineWorksCharacter::StartSprint);
    InputComponent->BindAction("Sprint", IE_Released, this, &AMOOnshineWorksCharacter::EndSprint);
	InputComponent->BindAction("Use", IE_Pressed, this, &AMOOnshineWorksCharacter::StartUse);
	InputComponent->BindAction("Use", IE_Released, this, &AMOOnshineWorksCharacter::EndUse);
    InputComponent->BindAction("Aim", IE_Pressed, this, &AMOOnshineWorksCharacter::StartAim);
    InputComponent->BindAction("Aim", IE_Released, this, &AMOOnshineWorksCharacter::EndAim);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMOOnshineWorksCharacter::Interact);
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &AMOOnshineWorksCharacter::NextWeapon);
	InputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AMOOnshineWorksCharacter::PreviousWeapon);
	InputComponent->BindAction("AnHero", IE_Pressed, this, &AMOOnshineWorksCharacter::AnHero);
    
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
	if (WeaponStrap->GetActiveGun())
	{
		if (!IsSprinting)
		{
			if (WeaponStrap->GetActiveGun()->CanCharge())
			{
				WeaponStrap->GetActiveGun()->StartCharge();
			}
			else
			{
				WeaponStrap->GetActiveGun()->Use();
			}
		}
	}
}

void AMOOnshineWorksCharacter::EndUse()
{
	if (WeaponStrap->GetActiveGun())
	{
		if (WeaponStrap->GetActiveGun()->CanCharge() && WeaponStrap->GetActiveGun()->IsCharging)
		{
			WeaponStrap->GetActiveGun()->EndCharge();
		}
	}
}

void AMOOnshineWorksCharacter::StartAim()
{
    if(IsSprinting == true)
	{
        EndSprint();
    }
    IsAiming = true;
}

void AMOOnshineWorksCharacter::EndAim()
{
    IsAiming = false;
}

void AMOOnshineWorksCharacter::NextWeapon()
{
	WeaponStrap->NextGun();
}

void AMOOnshineWorksCharacter::PreviousWeapon()
{
	WeaponStrap->PreviousGun();
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
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
        IsMovingForward = true;
    }
	else
	{
        IsMovingForward = false;
    }
}

void AMOOnshineWorksCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
		IsMovingSideway = true;
	}
	else
	{
		IsMovingSideway = false;
	}
}

void AMOOnshineWorksCharacter::StartSprint()
{
    if(Stamina > 0 && IsMovingForward == true)
    {
        //Adjust camera to sprint values
        //PerformCameraShake();
        //Adjust movement speed to sprint values & switch boolean to true
		GetCharacterMovement()->MaxWalkSpeed *= SprintMultiplier;
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
		GetCharacterMovement()->MaxWalkSpeed = (GetCharacterMovement()->MaxWalkSpeed / (SprintMultiplier * 100)) * 100;
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
		if (Item->GetClass()->IsChildOf(ACollectible::StaticClass()))
		{
			ACollectible* Collectable = Cast<ACollectible>(Item);
			if (Collectable) {
				Collectable->Collect(this);
			}
		}
	}
}
void AMOOnshineWorksCharacter::CheckForInteractables()
{
	TArray<AActor*> Items;
	InteractionSphere->GetOverlappingActors(Items);

	for (AActor* Item : Items)
	{
		if (Item->GetClass()->IsChildOf(AInteractable::StaticClass()))
		{
			AInteractable* Interactable = Cast<AInteractable>(Item);
			if (Interactable) 
			{
				Interactable->InRange(this);
				break;
			}
		}
	}
}


void AMOOnshineWorksCharacter::Interact()
{
	TArray<AActor*> Items;
	InteractionSphere->GetOverlappingActors(Items);

	for (AActor* Item : Items)
	{
		if (Item->GetClass()->IsChildOf(AInteractable::StaticClass()))
		{
			AInteractable* Interactable = Cast<AInteractable>(Item);

			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoCollisionFail = true;
			SpawnParams.Owner = this;
			slowDown = GetWorld()->SpawnActor<ASlowDownDebuff>(ASlowDownDebuff::StaticClass(), SpawnParams);
			JumpDebuff = GetWorld()->SpawnActor<ASuperJumpDebuff>(ASuperJumpDebuff::StaticClass(), SpawnParams);


			Debuffs.Add(JumpDebuff);
			Debuffs.Add(slowDown);

			//Debuffs[0]->SetDebuff(this);
			//Debuffs[1]->SetDebuff(this);


			if (Interactable) 
			{
				Interactable->Interact(this);
				break;
			}
		}
	}
}

void AMOOnshineWorksCharacter::AddKeyToKeyHolder(EDoorKey::Type KeyType) {
	kh->AddKey(KeyType);
}

bool AMOOnshineWorksCharacter::HasKeyHolder(EDoorKey::Type KeyType) {
	return kh->HasKey(KeyType);
}

void AMOOnshineWorksCharacter::EquipGun(APlayerGun* Gun)
{
	Gun->SetActorLocation(FirstPersonCameraComponent->GetComponentLocation());
	Gun->SetActorRelativeLocation(Gun->CharacterEquipOffset);
	Gun->AttachRootComponentTo(FirstPersonCameraComponent);
	Gun->SetActorRotation(FirstPersonCameraComponent->GetComponentRotation());
	Gun->SetActorRelativeRotation(Gun->CharacterEquipRotation);
	Gun->AmmoContainer = AmmoContainer;
	Gun->SetOwner(this);
	Gun->SetActiveGun();
	WeaponStrap->AddGun(Gun);
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
	CheckForInteractables();
	PerformCameraShake();

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


int32 AMOOnshineWorksCharacter::GetLightCurrentStage()
{
	return ceil(GetLightPercentage() / (1 / (LightStages - 1)));
}

float AMOOnshineWorksCharacter::GetLightStagePercentageFrom(int32 Stage)
{
	if (Stage > GetLightCurrentStage())
	{
		return 0.f;
	}
	else if (Stage < GetLightCurrentStage())
	{
		return 1.f;
	}

	float PercentagePerStage = 1 / (LightStages - 1);
	float CurrentStagePercentage = GetLightPercentage();

	while (CurrentStagePercentage > PercentagePerStage)
	{
		CurrentStagePercentage = CurrentStagePercentage - PercentagePerStage;
	}

	return CurrentStagePercentage / PercentagePerStage;
}

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
//	float ATRadius = ( GetLightMaxRadius() - GetLightMinRadius()) * GetLightPercentage() + GetLightMinRadius(); old linear light depletion

	float StagePercentageStep = 1 / (LightStages - 1);
	int32 ActualRange = GetLightMaxRadius() - GetLightMinRadius();
	float ATRadius = (ActualRange * StagePercentageStep * GetLightCurrentStage()) + GetLightMinRadius();

	Light->SetAttenuationRadius(ATRadius);
}

void AMOOnshineWorksCharacter::DealDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0)
	{
		Die();
	}
	else
	{
		OnDealDamage(Damage);
	}

}

void AMOOnshineWorksCharacter::OnDealDamage_Implementation(float Damage){
	
}

void AMOOnshineWorksCharacter::Die()
{

	if (!IsDeath)
	{
		IsDeath = true;
		OnDie();

		// Respawn should be called in the OnDie event in blueprints

		//((AMOOnshineWorksGameMode*)GetWorld()->GetAuthGameMode())->RestoreCheckpoint();
		//Destroy(); // currnetly character doesn't need to be destoryed but it might be easier save wise to jut spawn the actor again.
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


void AMOOnshineWorksCharacter::PerformCameraShake()
{
	if (!IsMovingForward && !IsMovingSideway && !IsSprinting)
	{
		if (!bIdleCameraShake)
		{
			StartShake(IdleCameraShake);
			bIdleCameraShake = true;
		}
	}
	else
	{
		StopShake(IdleCameraShake);
		bIdleCameraShake = false;
	}

	if (!IsSprinting && (IsMovingForward || IsMovingSideway))
	{
		if (!bWalkCameraShake)
		{
			StartShake(WalkCameraShake);
			bWalkCameraShake = true;
		}
	}
	else
	{
		StopShake(WalkCameraShake);
		bWalkCameraShake = false;
	}

	if (IsSprinting && (IsMovingForward || IsMovingSideway))
	{
		if (!bSprintCameraShake)
		{
			StartShake(SprintCameraShake);
			bSprintCameraShake = true;
		}
	}
	else
	{
		StopShake(SprintCameraShake);
		bSprintCameraShake = false;
	}
}

void AMOOnshineWorksCharacter::StartShake(TSubclassOf<UCameraShake> Shaker, float Scale)
{
	GetPlayerController()->ClientPlayCameraShake(Shaker, Scale, ECameraAnimPlaySpace::CameraLocal, FirstPersonCameraComponent->GetComponentRotation());
}

void AMOOnshineWorksCharacter::StopShake(TSubclassOf<UCameraShake> Shaker)
{
	GetPlayerController()->ClientStopCameraShake(Shaker);
}

//This function will kill all networked play
APlayerController* AMOOnshineWorksCharacter::GetPlayerController()
{
	return GetWorld()->GetFirstLocalPlayerFromController()->PlayerController;	
}

void AMOOnshineWorksCharacter::AnHero()
{
	//CharacterMovement->Velocity.Z = 200.0f; //kan niet vanaf de grond...
	FVector Impulse = FVector(0, 0, 1000);

	GetCharacterMovement()->Velocity = Impulse;
}

void AMOOnshineWorksCharacter::AddImpulseToCharacter(FVector Impulse)
{
	//Falling State
	FVector Location = GetActorLocation();
	Location.Z = Location.Z+10;
	SetActorLocation(Location);

	//physics van CapsuleComponent tijdelijk aanzetten!
	//GetCapsuleComponent()->SetSimulatePhysics(true);

	//Omhoog gooien
	GetCharacterMovement()->Velocity = Impulse;

	//Geef impulse aan character!
 	//CapsuleComponent->AddImpulse(Impulse, NAME_None, true);

	//GetCapsuleComponent()->SetSimulatePhysics(false);
}
