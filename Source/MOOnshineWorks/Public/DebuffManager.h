// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DebuffManager.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ADebuffManager : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void SetDebuff(AActor* Target);
	virtual void QuitDebuff();

	bool IsValid(FString nameDebuff);

	void SetTime(float Time, AActor* Target);

	//virtual void Start(ADebuffManager* Target);

	bool Repeat;

	FString name;

	TArray<FString> DebuffsActive;
	
};
