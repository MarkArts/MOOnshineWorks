// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DebuffManager.h"
#include "SlowDownDebuff.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASlowDownDebuff : public ADebuffManager
{
	GENERATED_UCLASS_BODY()

	virtual void SetDebuff(AActor* Target) override;
	virtual void QuitDebuff() override;

	
};
