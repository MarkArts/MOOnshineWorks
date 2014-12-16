// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerGun.h"
#include "Interactable.h"
#include "InteractableGun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AInteractableGun : public AInteractable
{
	GENERATED_UCLASS_BODY()

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = InteractableGun)
	//TSubobjectPtr<UStaticMeshComponent> InteractableMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InteractableGun)
	TSubclassOf<APlayerGun> Gun;

	virtual void OnInteract_Implementation(AActor* Target) override;
};