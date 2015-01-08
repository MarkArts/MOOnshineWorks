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

	NextStreamingLevelToLoad = 0;

	if (GetWorld()){

		SaveManager = (ASaveManager*)GetWorld()->SpawnActor(ASaveManager::StaticClass());
		SaveManager->Load();

		//BlueprintLoader::Get().AddBP(FName("AI_PegEnemyDark"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/PegAIDark/Blueprint/AI_PegEnemyDark"));
		//BlueprintLoader::Get().AddBP(FName("BP_Projectile"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Projectile"));
		//BlueprintLoader::Get().AddBP(FName("AI_BookEnemyLight"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/BookAILight/AI_BookEnemyLight"));
		//BlueprintLoader::Get().AddBP(FName("MyCharacter"), ANSI_TO_TCHAR("/Game/Blueprints/MyCharacter"));
		BlueprintLoader::Get().AddBP(FName("Crossbow"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Pistol/BP_Pistol"));
		BlueprintLoader::Get().AddBP(FName("Shotgun"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Shotgun/BP_Shotgun"));
		//BlueprintLoader::Get().AddBP(FName("Font"), ANSI_TO_TCHAR("/Game/Blueprints/HUDBlueprints/NewFont"));
		//BlueprintLoader::Get().AddBP(FName("ProjectileDeath"), ANSI_TO_TCHAR("/Game/Blueprints/BP_ProjectileDeath"));

		// set default pawn class to our Blueprinted character
		ConstructorHelpers::FClassFinder<APawn> BP(TEXT("/Game/Blueprints/MyCharacter"));
		DefaultPawnClass = BP.Class;

		static ConstructorHelpers::FObjectFinder<UBlueprint> VictoryPCOb(TEXT("Blueprint'/Game/Blueprints/HUDBlueprints/MainHud.MainHud'"));
		if (VictoryPCOb.Object != NULL)
		{
			HUDClass = (UClass*)VictoryPCOb.Object->GeneratedClass;
		}
	}
}

void AMOOnshineWorksGameMode::RestoreCheckpoint()
{

	ASaveManager* SaveManager = UHelpers::GetSaveManager(GetWorld());
	SaveManager->ResetData();

	/* Bad quik and dirty check to see if there was a checkpoint */
//	if (SaveManager->GetData()->Checkpoint.StreamingLevels.Num() <= 0)
//	{
		// Create checkpoint the first time the level is opened TODO: Do this beter
//		UHelpers::CreateCheckpoint((AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
//		return;
//	}

	/* TODO: If multyiply levels are unloaded the action will fire after the first on is done unloading */
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
	FCheckPointSave CheckPoint = SaveManager->GetData()->Checkpoint;

	if (CheckPoint.StreamingLevels.Num() > 0)
	{
		StreamingLevelsToLoad = CheckPoint.StreamingLevels;
		LoadNextStreamLevel();
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Checkpoint had no streaming levels."));
	}
}

void AMOOnshineWorksGameMode::LoadNextStreamLevel()
{

	FLatentActionInfo LatentActionInfo = FLatentActionInfo();
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LoadNextStreamLevel";
	LatentActionInfo.UUID = NextStreamingLevelToLoad+2;
	LatentActionInfo.Linkage = 0;

	if ( (NextStreamingLevelToLoad+1) < StreamingLevelsToLoad.Num() )
	{
		UGameplayStatics::LoadStreamLevel(GetWorld(), StreamingLevelsToLoad[NextStreamingLevelToLoad], true, true, LatentActionInfo);
		NextStreamingLevelToLoad++;
	}
	else{
		LatentActionInfo.ExecutionFunction = "AfterFinishingStreamLevels";
		UGameplayStatics::LoadStreamLevel(GetWorld(), StreamingLevelsToLoad[NextStreamingLevelToLoad], true, true, LatentActionInfo);
	}
}

void AMOOnshineWorksGameMode::AfterFinishingStreamLevels()
{
	StreamingLevelsToLoad.Empty();
	NextStreamingLevelToLoad = 0;

	AMOOnshineWorksCharacter* Player = Cast<AMOOnshineWorksCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->LoadPlayerSave(UHelpers::GetSaveManager(GetWorld())->GetData()->Player);
}