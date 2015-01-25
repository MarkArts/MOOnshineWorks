// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MainHUD.h"
#include "Helpers.h"


UHelpers::UHelpers(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}


FName UHelpers::GeneratePersistentId(AActor* Actor)
{
	if (Actor)
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

			FString ID = LevelName + PosString; // +RotString;

			return FName(*ID);
		}

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

	SaveManager->GetData()->Checkpoint = { 
		Actor->GetTransform().GetLocation(),
		Actor->GetTransform().Rotator(),
		GetActiveLevelsFrom(Actor->GetWorld()) 
	};
	SaveManager->GetData()->Player = Actor->CreatePlayerSave();
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

void UHelpers::DisplayText(UWorld* World, FString Text, int32 DisplayTime, FVector2D Position, FColor TextColor)
{

	/* If no position is set */
	if (Position == FVector2D(-1.f, -1.f))
	{
		//const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		//Position = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
		Position = FVector2D(0.f, -200.f); //(ViewportSize.Y / 2) * 0.8 );
	}

	AMainHUD* MainHUD = (AMainHUD*)UGameplayStatics::GetPlayerController(World, 0)->GetHUD();
	if (MainHUD)
	{
		FDisplayString DisplayString = {
			Text,
			Position,
			TextColor,
			FVector2D(1.f, 1.f),
			DisplayTime,
			1
		};

		MainHUD->AddDisplayString(DisplayString);
	}
}

void UHelpers::ApplyActorSave(FActorSave ActorSave, AActor* Actor)
{
	if (ActorSave.StopSpawn)
	{
		Actor->Destroy();
	}
	else{
		Actor->SetActorHiddenInGame(ActorSave.Hidden);
		Actor->SetActorTransform(FTransform(
			ActorSave.Rotation,
			ActorSave.Postition,
			FVector(1.f,1.f,1.f)
		));
	}
}

FActorSave UHelpers::CreateActorSave(AActor* Actor, bool StopSpawn, bool Hidden, FName Id)
{

	if (Id == TEXT(""))
	{
		Id = GeneratePersistentId(Actor);
	}

	FActorSave ActorSave = FActorSave();

	ActorSave.Id = Id;
	ActorSave.StopSpawn = StopSpawn;
	ActorSave.Postition = Actor->GetTransform().GetLocation();
	ActorSave.Rotation = Actor->GetTransform().Rotator();
	ActorSave.Hidden = Hidden;

	return ActorSave;
}