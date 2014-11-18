// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "AI_BasicController.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Health;

	/** Defense */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Defense;

	/** Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* Behavior;

	void StartSprint();

	void StartWalk();

	UFUNCTION(BlueprintCallable, Category = AIStats)
	void ChangeLightDark(bool CurrentDarkLight);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIStats)
	int32 LightType;
};

enum EnemyLightType {
	Dark,
	Light
};