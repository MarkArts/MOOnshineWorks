// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "AmmoContainer.h"
#include "WeaponStrap.h"
#include "Item.h"
#include "Gun.h"
#include "Pistol.h"
#include "DoorKey.h"
#include "KeyHolder.h"
#include "DebuffManager.h"
#include "SuperJumpDebuff.h"
#include "SlowDownDebuff.h"
#include "GameFramework/Character.h"
#include "AI_BasicController.h"
#include "MOOnshineWorksCharacter.generated.h"

UCLASS(config=Game)
class AMOOnshineWorksCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AMOOnshineWorksCharacter(const class FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void AnHero();

	/** Make Character able to produce sound */
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	UPawnNoiseEmitterComponent* NoiseEmitter;
	
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = Ammo)
	AAmmoContainer* AmmoContainer;
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = Guns)
	AWeaponStrap* WeaponStrap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MOOnshine)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MOOnshine)
	float BaseLookUpRate;
	
    /* Characters base mana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshine) //BlueprintReadOnly
    float BaseMana;
    
	/* Characters current mana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshine) //BlueprintReadOnly
	float CurrentMana;

	/* AI Dark(true)/Light(false)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshine) //BlueprintReadOnly
	bool DarkLight;
    
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
    UTexture2D* GetAvatar();
//private:
    /* Characters health */
	UPROPERTY(EditAnywhere, Category = MOOnshine) //BlueprintReadOnly
    float BaseHealth;
	UPROPERTY(EditAnywhere, Category = MOOnshine) //BlueprintReadOnly
	float CurrentHealth;
//public:
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetBaseHealth(float NewBaseHealth);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetBaseHealth();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetCurrentHealth(float NewCurrentHealth);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
    float GetCurrentMana();
    
/* Light */
//private:
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float LightPercentage;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float LightDimSpeed;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float LightMaxRadius;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float LightMinRadius;
//public:
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float LightStages;
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetLightPercentage(float NewLightPercentage);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetLightPercentage();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetLightDimSpeed(float NewLightDimSpeed);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetLightDimSpeed();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetLightMaxRadius(float NewLightMaxRadius);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetLightMaxRadius();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetLightMinRadius(float NewLightMinRadius);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetLightMinRadius();

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	int32 GetLightCurrentStage();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetLightStagePercentageFrom(int32 Stage);

	void UpdateLightRadius(float DeltaSeconds);
	void SetLightRadius();

    // Stamina logic
//private:
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float BaseStamina;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
	float Stamina;
    UPROPERTY(EditAnywhere, Category = MOOnshine)
    float CharacterWalkSpeed;
//public:
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetBaseStamina(float NewBastStamina);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetBaseStamina();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void SetStamina(float New_Stamina);
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	float GetStamina();

    //Standard camera values
    float baseCameraZoom;
    float baseCameraAimZoom;
    float baseCameraSprintZoom;
    FVector baseCameraOffset;
    FVector baseZoomOffset;
    FVector baseSprintOffset;

	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> IdleCameraShake;
	bool bIdleCameraShake;
	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> WalkCameraShake;
	bool bWalkCameraShake;
	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> SprintCameraShake;
	bool bSprintCameraShake;

	void PerformCameraShake();
	void StartShake(TSubclassOf<UCameraShake> Shaker, float Scale = 1.f);
	void StopShake(TSubclassOf<UCameraShake> Shaker);
	APlayerController* GetPlayerController();
	
	/** Collection volume surrounds the character to check if any pickup objects are in range to collect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	USphereComponent* CollectionSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	UPointLightComponent* Light;

    // Sprint logic
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
    bool IsSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
    float SprintMultiplier;
    
    //Boolean which contains aiming state (false / true)
    bool IsAiming;

    //Boolean which contains moving state (false / true)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
    bool IsMovingForward;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CharacterMovement)
    bool IsMovingSideway;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void EquipGun(APlayerGun* Gun);

	UFUNCTION(BlueprintNativeEvent, Category = MOOnshine)
	void OnDealDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void DealDamage(float Damage);

	KeyHolder* kh;
	ASlowDownDebuff* slowDown;
	ASuperJumpDebuff* JumpDebuff;
	TArray<ADebuffManager*> Debuffs;

	//DebuffManager* debuffManager;

	UPROPERTY(VisibleAnyWhere, Category = MOOnshine)
	bool IsDeath;
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void Die();
	UFUNCTION(BlueprintImplementableEvent, Category = MOOnshine)
	void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshine)
	TArray<ADoorKey*> KeyPack;

	void AddKeyToKeyHolder(EDoorKey::Type KeyType);

	bool HasKeyHolder(EDoorKey::Type KeyType);
    
    // Character avatar
	UPROPERTY(EditAnywhere, Category = MOOnshine)
    UTexture2D* StandardAvatar;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
    UTexture2D* AvatarLowHP;
	UPROPERTY(EditAnywhere, Category = MOOnshine)
    UTexture2D* AvatarVeryLowHP;

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void Respawn();

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	FPlayerSave CreatePlayerSave();
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void LoadPlayerSave(FPlayerSave PlayerSave);

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void AddImpulseToCharacter(FVector Impulse);

protected:

	//Called by CollectItems() to use the Blueprinted functionality
	UFUNCTION(BlueprintImplementableEvent, Category = MOOnshine)
	void ManaUp(float Mana);

	//Called when we press a key, to collect any item inside the SphereComponent
	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void CollectItems();

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void CheckForInteractables();
    
	/** Called for useItem input */
	void StartUse();
	void EndUse();
    
    /** Called for start aim input */
    void StartAim();
    void EndAim();
    
    /** Called for sprint input */
    void StartSprint();
    void EndSprint();
    
    /** Calculates stamina of character*/
    void CalcStamina();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void NextWeapon();
	void PreviousWeapon();

	void Interact();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void ReceiveBeginPlay() override;
};

