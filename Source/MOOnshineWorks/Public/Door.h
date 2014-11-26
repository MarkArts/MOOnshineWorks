// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ADoor : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void DoorOpen();

	bool DoorClosed;
	
};
