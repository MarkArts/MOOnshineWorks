// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "BaseLevelScriptActor.h"


ABaseLevelScriptActor::ABaseLevelScriptActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void ABaseLevelScriptActor::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		ASaveManager* SaveManager = UHelpers::GetSaveManager(World);
		if (SaveManager->GetData()->Checkpoint.StreamingLevels.Num() <= 0)
		{
			// no chekpoint so first time playing


			/* 
				Because the player isn't probaply initialized here yet we create out save game custom
				This is currently a work around and all default values set must be hardcoded here
			*/

			ASaveManager* SaveManager = UHelpers::GetSaveManager(GetWorld());

			APlayerStart* PlayerStart = World->GetAuthGameMode()->PlayerStarts[0];

			SaveManager->GetData()->Checkpoint = {
				PlayerStart->GetTransform().GetLocation(),
				PlayerStart->GetTransform().Rotator(),
				UHelpers::GetActiveLevelsFrom(GetWorld())
			};

			TArray<FName> Weapons;
			TArray<int32> AmmoCounters;
			AmmoCounters.Add(15);
			AmmoCounters.Add(10);

			SaveManager->GetData()->Player = {
				PlayerStart->GetTransform().GetLocation(),
				PlayerStart->GetTransform().Rotator(),
				Weapons,
				AmmoCounters
			};
			
			SaveManager->Save();

			UGameplayStatics::GetPlayerPawn(World, 0)->SetActorTransform(GetWorld()->GetAuthGameMode()->PlayerStarts[0]->GetTransform());
		}
		else{
			((AMOOnshineWorksGameMode*)World->GetAuthGameMode())->RestoreCheckpoint();
		}
	}
}