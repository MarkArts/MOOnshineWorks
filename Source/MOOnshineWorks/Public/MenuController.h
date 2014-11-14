// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AMenuController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "MOOnshine")
	void SetMousePosition(float LocationX, float LocationY);

	UFUNCTION(BlueprintCallable, Category = "MOOnshine")
	AActor* getPointedObject();
	
};
