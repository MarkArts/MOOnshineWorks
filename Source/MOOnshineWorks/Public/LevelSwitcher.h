// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ALevelSwitcher : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moonshine)
	FName TargetLevel;

public:

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void Activate();
};
