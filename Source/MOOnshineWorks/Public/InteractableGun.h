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
	GENERATED_BODY()
public:
	AInteractableGun(const class FObjectInitializer& PCIP);

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = InteractableGun)
	//TSubobjectPtr<UStaticMeshComponent> InteractableMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InteractableGun)
	TSubclassOf<APlayerGun> Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InteractableGun)
	int32 AmmoGivenIfHasGun;

	virtual void OnInteract_Implementation(AActor* Target) override;
};
