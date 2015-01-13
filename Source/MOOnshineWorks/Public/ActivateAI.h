// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActivateAI.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AActivateAI : public AActor
{
	GENERATED_BODY()
public:
	AActivateAI(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ActivateAI)
	TSubclassOf<AActor> SpawnClass;

	UFUNCTION(BlueprintCallable, Category = MOO)
	void Activate();

	UFUNCTION(BlueprintCallable, Category = MOO)
	void Change();
};
