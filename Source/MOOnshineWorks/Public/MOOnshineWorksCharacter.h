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
   
	/* Characters speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
		float BaseSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStats) //BlueprintReadOnly
		float SpeedFactor;

private:
    /* Characters health */
    UPROPERTY(VisibleAnywhere, Category = CharacterStats) //BlueprintReadOnly
    float BaseHealth;
	UPROPERTY(VisibleAnywhere, Category = CharacterStats) //BlueprintReadOnly
	float CurrentHealth;
public:
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetBaseHealth(float NewBaseHealth);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetBaseHealth();
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetCurrentHealth(float NewCurrentHealth);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetCurrentHealth();

	/* Light */
private:
	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
	float LightPercentage;
	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
	float DimSpeed;
	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
	float MaxRadius;
public:
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetLightPercentage(float NewLightPercentage);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetLightPercentage();
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetDimSpeed(float NewDimSpeed);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetDimSpeed();
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetMaxRadius(float NewMaxRadius);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetMaxRadius();
	
	void UpdateLightRadius(float DeltaSeconds);
	void SetLightRadius();

    // Stamina logic
private:
	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
	float BaseStamina;
	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
	float Stamina;
public:
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetBaseStamina(float NewBastStamina);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetBaseStamina();
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void SetStamina(float New_Stamina);
	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	float GetStamina();

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

