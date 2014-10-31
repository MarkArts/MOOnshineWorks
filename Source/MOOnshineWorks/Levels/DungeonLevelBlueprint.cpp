// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DungeonLevelBlueprint.h"


ADungeonLevelBlueprint::ADungeonLevelBlueprint(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ADungeonLevelBlueprint::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
}

void ADungeonLevelBlueprint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADungeonLevelBlueprint::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}