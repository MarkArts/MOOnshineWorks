// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Helpers.h"


UHelpers::UHelpers(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


FName UHelpers::GeneratePersistentId(AActor* Actor)
{
	UWorld* World = Actor->GetWorld();
	if (World)
	{
		FVector Pos = Actor->GetActorLocation();
		FString PosString = FString::SanitizeFloat(round(Pos.X)) + FString::SanitizeFloat(round(Pos.Y)) + FString::SanitizeFloat(round(Pos.Z));

		FRotator Rot = Actor->GetActorRotation();
		FString RotString = FString::SanitizeFloat(round(Rot.Yaw)) + FString::SanitizeFloat(round(Rot.Roll)) + FString::SanitizeFloat(round(Rot.Pitch));

		FString Name = Actor->GetName();
		FString LevelName = Actor->GetLevel()->GetName();

		FString ID = Name + LevelName + PosString + RotString;

		return FName(*ID);
	}

	return FName();
}

ASaveManager* UHelpers::GetSaveManager(UWorld* World)
{
	return ((AMOOnshineWorksGameMode*)UGameplayStatics::GetGameMode(World))->SaveManager;
}

void UHelpers::CreateCheckpoint(AMOOnshineWorksCharacter* Actor)
{
	ASaveManager* SaveManager = GetSaveManager(Actor->GetWorld());

	SaveManager->GetData()->Checkpoint = { Actor->GetTransform(), GetActiveLevelsFrom(Actor->GetWorld()) };
	SaveManager->Save();
}

TArray<FName> UHelpers::GetActiveLevelsFrom(UWorld* World)
{
	TArray<FName> ActiveLevels;

	TArray<ULevelStreaming*> StreamingLevels = World->StreamingLevels;
	int8 LevelNum = StreamingLevels.Num();

	for (int8 I = 0; I < LevelNum; I++)
	{
		if (StreamingLevels[I]->bShouldBeLoaded > 0)
		{
			ActiveLevels.Add(StreamingLevels[I]->PackageNameToLoad);
		}
	}

	return ActiveLevels;
}