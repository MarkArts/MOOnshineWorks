// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DoorKey.h"
#include "Interactable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ADoor : public AInteractable
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintNativeEvent, Category = "Moonshine")
	void DoorOpen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	bool DoorClosed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FRotator BeginningRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moonshine")
	TEnumAsByte<EDoorKey::Type> KeyName;

	virtual void OnInteract_Implementation(AActor* Target) override;
};
