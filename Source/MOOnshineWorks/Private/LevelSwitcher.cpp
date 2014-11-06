// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Levels/DungeonLevelBlueprint.h"
#include "LevelSwitcher.h"

ALevelSwitcher::ALevelSwitcher(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ALevelSwitcher::Activate()
{
	UWorld* currentWorld = GetWorld();
	ULevel* actor = currentWorld->GetCurrentLevel();
	ALevelScriptActor* levelScript = currentWorld->GetLevelScriptActor();
	ADungeonLevelBlueprint* blp = (ADungeonLevelBlueprint*)levelScript;
	blp->LoadLevel(TargetLevel, "");
}
