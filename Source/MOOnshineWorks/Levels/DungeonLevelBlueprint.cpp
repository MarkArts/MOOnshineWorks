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

	UnloadCurrentLevel(FLatentActionInfo());

	ULevelStreaming* NewLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), TargetLevel);
	//NewLevel = CreateLevelInstance(NewLevel, UniqueName);
	
	if (NewLevel){
		NewLevel->bShouldBeLoaded = true;
		NewLevel->bShouldBeVisible = true;
	/*	NewLevel->LevelTransform = FTransform(
			FQuat(0.f, 0.f, 0.f, 0.f),
			FVector(0.f, 0.f, 0.f),
			FVector(0.f, 0.f, 0.f)
			); */

		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->TeleportTo(FVector(100.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

		CurrentLevel = TargetLevel.ToString();
		//CurrentLevel = UniqueName;
	}
}
ULevelStreaming* ADungeonLevelBlueprint::CreateLevelInstance(ULevelStreaming* level, FString& InstanceUniqueName)
{
	ULevelStreaming* StreamingLevelInstance = nullptr;

	UWorld* InWorld = level->GetWorld();
	if (InWorld)
	{
		// Create instance long package name
		FString InstanceShortPackageName = InWorld->StreamingLevelsPrefix + FPackageName::GetShortName(InstanceUniqueName);
		FString InstancePackagePath = FPackageName::GetLongPackagePath(level->GetWorldAssetPackageName()) + TEXT("/");
		FName InstanceUniquePackageName = FName(*(InstancePackagePath + InstanceShortPackageName));

		// check if instance name is unique among existing streaming level objects
		const bool bUniqueName = (InWorld->StreamingLevels.FindMatch(ULevelStreaming::FPackageNameMatcher(InstanceUniquePackageName)) == INDEX_NONE);

		if (bUniqueName)
		{
			StreamingLevelInstance = Cast<ULevelStreaming>(StaticConstructObject(level->GetClass(), InWorld, NAME_None, RF_Transient, NULL));
			// new level streaming instance will load the same map package as this object
			StreamingLevelInstance->PackageNameToLoad = (level->PackageNameToLoad == NAME_None ? level->GetWorldAssetPackageFName() : level->PackageNameToLoad);
			// under a provided unique name
			StreamingLevelInstance->SetWorldAssetByPackageName(InstanceUniquePackageName);
			StreamingLevelInstance->bShouldBeLoaded = false;
			StreamingLevelInstance->bShouldBeVisible = false;
			StreamingLevelInstance->LevelTransform = level->LevelTransform;

			// add a new instance to streaming level list
			InWorld->StreamingLevels.Add(StreamingLevelInstance);
		}
		else
		{
			UE_LOG(LogStreaming, Warning, TEXT("Provided streaming level instance name is not unique: %s"), *InstanceUniquePackageName.ToString());
		}
	}

	return StreamingLevelInstance;
}
void ADungeonLevelBlueprint::UnloadCurrentLevel(FLatentActionInfo LatentAction)
{
	if (CurrentLevel != FString("") )
	{
		UGameplayStatics::UnloadStreamLevel(GetWorld(), FName(*CurrentLevel), LatentAction);
	}
} 