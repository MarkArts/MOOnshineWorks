// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksGameMode.h"
#include "Socket.h"
#include "Helpers.h"
#include "BaseLevelScriptActor.h"
#include "MOOnshineWorksCharacter.h"

AMOOnshineWorksGameMode::AMOOnshineWorksGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	if (GetWorld()){
		SaveManager = (ASaveManager*)GetWorld()->SpawnActor(ASaveManager::StaticClass());
		SaveManager->Load();

	}
}

void AMOOnshineWorksGameMode::RestoreCheckpoint()
{

	ASaveManager* SaveManager = UHelpers::GetSaveManager(GetWorld());
	SaveManager->ResetData();

	/* If multyiply levels are unloaded the action will fire after the first on is done unloading */
	FLatentActionInfo LatentActionInfo = FLatentActionInfo();
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LoadCheckpoint";
	LatentActionInfo.UUID = 1;
	LatentActionInfo.Linkage = 0;

	RemoveLevelStreaming(LatentActionInfo);
}

void AMOOnshineWorksGameMode::RemoveLevelStreaming(FLatentActionInfo LatentActionInfo)
{
	TArray<ULevelStreaming*> Levels = GetWorld()->StreamingLevels;
	int32 LevelNum = Levels.Num();

	for (int32 i = 0; i < LevelNum; i++)
	{
		if (Levels[i]->bShouldBeLoaded > 0)
		{
			UGameplayStatics::UnloadStreamLevel(GetWorld(), Levels[i]->PackageNameToLoad, LatentActionInfo);
		}
	}
}

void AMOOnshineWorksGameMode::LoadCheckpoint()
{
	FCheckPointSave CheckPoint = SaveManager->GetData()->Player.Checkpoint;

	if (CheckPoint.StreamingLevel != FName())
	{
		UGameplayStatics::LoadStreamLevel(GetWorld(), CheckPoint.StreamingLevel, true, false, FLatentActionInfo());
		/* squilli error about transform not existing is false*/
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorTransform(CheckPoint.TransForm);
	}
	else{
		/* This should be replaced with code that works in every level */
		UGameplayStatics::LoadStreamLevel(GetWorld(), FName("Part2"), true, false, FLatentActionInfo());
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorTransform(PlayerStarts[0]->GetTransform());
	}
}