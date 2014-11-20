// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MOOnshineWorksGameMode.h"
#include "BlueprintLoader.h"
#include "Gun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API APistol : public AGun
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ReceiveBeginPlay() override;
	
};
