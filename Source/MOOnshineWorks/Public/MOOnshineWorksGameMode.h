// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "BlueprintLoader.h"
#include "GameFramework/GameMode.h"
#include "SaveManager.h"
#include "MOOnshineWorksGameMode.generated.h"

UCLASS(minimalapi)
class AMOOnshineWorksGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	//ASocket* Socket;

	ASaveManager* SaveManager;
	UFUNCTION()
	void RestoreCheckpoint();
	UFUNCTION()
	void RemoveLevelStreaming(FLatentActionInfo LatentActionInfo);
	UFUNCTION()
	void LoadCheckpoint();
};



