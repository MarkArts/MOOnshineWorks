// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DungeonLevelBlueprint.h"
#include "Engine/LevelStreaming.h"

ADungeonLevelBlueprint::ADungeonLevelBlueprint(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CurrentLevel = "";
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

void ADungeonLevelBlueprint::LoadLevel(FName TargetLevel, FString UniqueName)
{

	UnloadCurrentLevel();

	ULevelStreaming* NewLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), TargetLevel);
	//NewLevel = NewLevel->CreateInstance(UniqueName);
	NewLevel->bShouldBeLoaded = true;
	NewLevel->bShouldBeVisible = true;
	NewLevel->LevelTransform = FTransform(
		FQuat(0.f, 0.f, 0.f, 0.f),
		FVector(0.f, 0.f, 0.f),
		FVector(0.f, 0.f, 0.f)
	);

//	CurrentLevel = UniqueName;
	CurrentLevel = TargetLevel.ToString();
}


void ADungeonLevelBlueprint::UnloadCurrentLevel()
{
	if (CurrentLevel != FString("") )
	{
		UGameplayStatics::UnloadStreamLevel(GetWorld(), FName(*CurrentLevel), FLatentActionInfo());
	}
} 