// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Item.h"
#include "Gun.h"
#include "Pistol.h"
#include "GameFramework/Character.h"
#include "MOOnshineWorksCharacter.generated.h"

UCLASS(config=Game)
class AMOOnshineWorksCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	AItem* activeItem;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
    /* Characters base mana */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
    float BaseMana;
    
	/* Characters current mana */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
	float CurrentMana;
    
    /* Characters base health */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
    float BaseHealth;
    
    /* Characters current health */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
	float CurrentHealth;

	/* Characters basespeed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
	float BaseSpeed;

	/* Characters increase */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
	float SpeedFactor;

	/* Light */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float LightPercentage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float DimSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float MaxRadius;
	void UpdateLightRadius(float DeltaSeconds);
    
    // Float that contains the character stamina
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats)
    float BaseStamina;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats)
    float Stamina;
	void SetStamina(float New_Stamina) { Stamina = New_Stamina; };
	float GetStamina() { return Stamina; };

    //Standard camera values
    float baseCameraZoom;
    float baseCameraAimZoom;
    float baseCameraSprintZoom;
    FVector baseCameraOffset;
    FVector baseZoomOffset;
    FVector baseSprintOffset;
    
	/** Collection volume surrounds the character to check if any pickup objects are in range to collect */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<USphereComponent> CollectionSphere;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubobjectPtr<UPointLightComponent> Light;

    //Boolean which contains sprinting state (false / true)
    bool IsSprinting;
    
    //Boolean which contains aiming state (false / true)
    bool IsAiming;

    //Boolean which contains moving state (false / true)
    bool IsMovingForward;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = Pistol)
	void equipPistol();

	void DealDamage(float Damage);

protected:

	//Called by CollectItems() to use the Blueprinted functionality
	UFUNCTION(BlueprintImplementableEvent, Category = Items)
	void ManaUp(float Mana);

	//Called when we press a key, to collect any item inside the SphereComponent
	UFUNCTION(BlueprintCallable, Category = Items)
	void CollectItems();
    
	/** Called for useItem input */
	void StartUse();
	void EndUse();

    /** Called for aim input */
    /** This function needs to be reviewed, doesn't work somehow */
    //void PerformCameraShake();
    
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

	void reload();

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void ReceiveBeginPlay() override;

};

