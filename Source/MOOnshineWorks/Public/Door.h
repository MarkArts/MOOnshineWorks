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

	UFUNCTION(BlueprintNativeEvent, Category = "Moonshine")
	void DoorOpen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	class AMatineeActor* MatineeActorFile;

	UPROPERTY(EditAnywhere, Category = MOOnshineWorks)
	class ATriggerBox* TriggerBoxFile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	bool DoorClosed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FRotator BeginningRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FVector BeginningPos;


	
};
