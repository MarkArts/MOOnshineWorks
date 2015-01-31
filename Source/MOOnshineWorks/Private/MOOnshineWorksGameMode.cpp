// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksGameMode.h"
#include "Socket.h"
#include "Helpers.h"
#include "BaseLevelScriptActor.h"
#include "MOOnshineWorksCharacter.h"

AMOOnshineWorksGameMode::AMOOnshineWorksGameMode(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

	NextStreamingLevelToLoad = 0;
	NextStreamingLevelToUnLoad = 0;

	if (GetWorld()){

		SaveManager = (ASaveManager*)GetWorld()->SpawnActor(ASaveManager::StaticClass());
		SaveManager->Load();

		//BlueprintLoader::Get().AddBP(FName("AI_PegEnemyDark"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/PegAIDark/Blueprint/AI_PegEnemyDark"));
		//BlueprintLoader::Get().AddBP(FName("BP_Projectile"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Projectile"));
		//BlueprintLoader::Get().AddBP(FName("AI_BookEnemyLight"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/BookAILight/AI_BookEnemyLight"));
		//BlueprintLoader::Get().AddBP(FName("MyCharacter"), ANSI_TO_TCHAR("/Game/Blueprints/MyCharacter"));
		BlueprintLoader::Get().AddBP(FName("Plungebow"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Pistol/BP_Pistol"));
		BlueprintLoader::Get().AddBP(FName("Locomotion"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Shotgun/BP_Shotgun"));
		BlueprintLoader::Get().AddBP(FName("Teazooka"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Bazooka/BP_Bazooka"));
		//BlueprintLoader::Get().AddBP(FName("Font"), ANSI_TO_TCHAR("/Game/Blueprints/HUDBlueprints/NewFont"));
		//BlueprintLoader::Get().AddBP(FName("ProjectileDeath"), ANSI_TO_TCHAR("/Game/Blueprints/BP_ProjectileDeath"));

		// set default pawn class to our Blueprinted character
		ConstructorHelpers::FClassFinder<APawn> PawnBP(TEXT("/Game/Blueprints/MyCharacter"));
		DefaultPawnClass = PawnBP.Class;

		ConstructorHelpers::FClassFinder<AHUD> HUDBP(TEXT("/Game/Blueprints/HUDBlueprints/MainHud"));
		HUDClass = HUDBP.Class;
	}
}

void AMOOnshineWorksGameMode::RestoreCheckpoint()
{

	ASaveManager* SaveManager = UHelpers::GetSaveManager(GetWorld());
	SaveManager->ResetData();

	RemoveLevelStreaming();
}

void AMOOnshineWorksGameMode::RemoveLevelStreaming()
{
	StreamingLevelsToUnLoad = UHelpers::GetActiveLevelsFrom(GetWorld());

	if (StreamingLevelsToUnLoad.Num())
	{
		UnLoadNextStreamLevel();
	}
	else{
		AfterFinishingUnloadStreamLevels();
	}
}

void AMOOnshineWorksGameMode::UnLoadNextStreamLevel()
{

	FLatentActionInfo LatentActionInfo = FLatentActionInfo();
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "UnLoadNextStreamLevel";
	LatentActionInfo.UUID = NextStreamingLevelToUnLoad + 2;
	LatentActionInfo.Linkage = 0;

	if ((NextStreamingLevelToUnLoad + 1) < StreamingLevelsToUnLoad.Num())
	{
		UGameplayStatics::UnloadStreamLevel(GetWorld(), StreamingLevelsToUnLoad[NextStreamingLevelToUnLoad], LatentActionInfo);
		NextStreamingLevelToUnLoad++;
	}
	else{
		LatentActionInfo.ExecutionFunction = "AfterFinishingUnloadStreamLevels";
		UGameplayStatics::UnloadStreamLevel(GetWorld(), StreamingLevelsToUnLoad[NextStreamingLevelToUnLoad], LatentActionInfo);
	}
}

void AMOOnshineWorksGameMode::AfterFinishingUnloadStreamLevels()
{
	StreamingLevelsToUnLoad.Empty();
	NextStreamingLevelToUnLoad = 0;

	LoadCheckpoint();
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