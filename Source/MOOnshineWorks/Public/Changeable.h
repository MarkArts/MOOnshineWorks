// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AI_BasicController.h"
#include "Changeable.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AChangeable : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TSubclassOf<APawn> TargetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintNativeEvent, Category = MOO)
	void Activate();

	UFUNCTION(BlueprintCallable, Category = MOO)
	void Change();

	
};
