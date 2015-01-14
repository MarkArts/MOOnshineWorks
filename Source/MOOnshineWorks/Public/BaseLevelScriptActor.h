// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "BaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ABaseLevelScriptActor(const class FObjectInitializer& PCIP);
	protected:
	virtual void ReceiveBeginPlay() override;
};
