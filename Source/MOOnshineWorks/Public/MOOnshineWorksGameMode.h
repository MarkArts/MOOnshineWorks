// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "BlueprintLoader.h"
#include "GameFramework/GameMode.h"
#include "SaveManager.h"
#include "MOOnshineWorksGameMode.generated.h"

UCLASS(minimalapi)
class AMOOnshineWorksGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMOOnshineWorksGameMode(const class FObjectInitializer& PCIP);
	//ASocket* Socket;

	UPROPERTY(BlueprintReadOnly, Category=MOO)
	ASaveManager* SaveManager;
	UFUNCTION(BlueprintCallable, Category = MOO)
	void RestoreCheckpoint();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void RemoveLevelStreaming(FLatentActionInfo LatentActionInfo);
	UFUNCTION(BlueprintCallable, Category = MOO)
	void LoadCheckpoint();

	UFUNCTION(BlueprintCallable, Category = MOO)
	void LoadNextStreamLevel();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void AfterFinishingStreamLevels();

	TArray<FName> StreamingLevelsToLoad;
	int32 NextStreamingLevelToLoad;
};



