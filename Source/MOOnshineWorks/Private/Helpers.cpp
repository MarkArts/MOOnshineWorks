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

void UHelpers::CreateCheckpoint(AMOOnshineWorksCharacter* Actor, FName Level)
{
	ASaveManager* SaveManager = GetSaveManager(Actor->GetWorld());
	SaveManager->GetData()->Player.Checkpoint = { Actor->GetTransform(), Level };
	SaveManager->Save();
}