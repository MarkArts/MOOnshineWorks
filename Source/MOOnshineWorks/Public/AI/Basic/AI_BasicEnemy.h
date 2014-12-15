// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "AI_BasicController.h"
#include "Materials/Material.h"
#include "AI_BasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AAI_BasicEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Pawn sensing Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Awareness)
	TSubobjectPtr<class UPawnSensingComponent> PawnSensor;

	UFUNCTION()
	void PostInitializeComponents();

	UFUNCTION(BlueprintCallable, Category = Items)
	void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = Items)
	void OnSeePawn(APawn *OtherPawn);

	/** Health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float Health;

	/** Defense */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float Defense;

	/** Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float Speed;

	/** Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	float Damage;

	/** Check if AI is active, else he cant be hit/killed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	bool CanBeHit;

	/** Should Patrol or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStats)
	bool AIPatrol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AIStats)
	int32 LightType;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* Behavior;

	void StartSprint();

	void StartWalk();

	UFUNCTION(BlueprintCallable, Category = AIStats)
	void ChangeLightDark(bool CurrentDarkLight);

	UFUNCTION(BlueprintCallable, Category = AIStats)
	void DealDamage(float DamageInflicted);

	UFUNCTION(BlueprintCallable, Category = AIStats)
	void Die();

	UFUNCTION(BlueprintCallable, Category = AIStats)
	FName GetPersistentId();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	UMaterial* TheMaterial;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	//UMaterialInterface* Base_Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActivateEnemy)
	TSubclassOf<AActor> DeathBlueprint;

private:
	FName PersistentId;

protected:
	virtual void ReceiveBeginPlay() override;
};

enum EnemyLightType {
	Dark,
	Light
};
