// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DungeonLevelBlueprint.h"
#include "LevelSwitcher.h"

ALevelSwitcher::ALevelSwitcher(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	IsActive = true;
}

void ALevelSwitcher::Activate()
{
	if (IsActive){

		IsActive = false;

		//UGameplayStatics::OpenLevel(GetWorld(), FName("level2"), true)

		UWorld* currentWorld = GetWorld();
		ULevel* actor = currentWorld->GetCurrentLevel();
		ALevelScriptActor* levelScript = currentWorld->GetLevelScriptActor();
		ADungeonLevelBlueprint* blp = (ADungeonLevelBlueprint*)levelScript;
		blp->LoadLevel(TargetLevel, TargetLevel.ToString() + FString("inst"));
	}
}
