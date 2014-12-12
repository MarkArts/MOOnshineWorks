// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AInteractable : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool Active;

	UFUNCTION(BluePrintNativeEvent, Category = MOO)
	void OnInteract(AActor* Target);
	UFUNCTION(BlueprintCallable, Category = MOO)
	virtual void Interact(AActor* Target);
};
