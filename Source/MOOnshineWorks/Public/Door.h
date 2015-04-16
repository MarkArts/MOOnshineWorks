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
	GENERATED_BODY()
public:
	ADoor(const class FObjectInitializer& PCIP);

	UFUNCTION(BlueprintNativeEvent, Category = "Moonshine")
	void DoorOpen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	bool DoorClosed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FString OpenText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FRotator BeginningRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moonshine")
	TEnumAsByte<EDoorKey::Type> KeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FString CanUseDisplayText;

	virtual void OnInteract_Implementation(AActor* Target) override;
	virtual void InRange(AActor* Target) override;
};
