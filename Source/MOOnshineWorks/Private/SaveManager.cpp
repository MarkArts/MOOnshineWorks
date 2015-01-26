// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "SaveManager.h"

ASaveManager::ASaveManager(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	SaveSlotName = TEXT("MoonshineWorksSave");

	UserIndex = 0;
}

void ASaveManager::Load()
{
	UMOOSaveGame* LoadGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (LoadGameInstance)
	{
		SaveData = LoadGameInstance->Data;
	}
	else
	{
		SaveData = FSave();
	}

	ResetData();
}
void ASaveManager::ResetData()
{
	SaveDataCandidate = SaveData;
}
void ASaveManager::RemoveSave()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Removed Save Game");
	UMOOSaveGame* SaveGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::CreateSaveGameObject(UMOOSaveGame::StaticClass()));
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
	Load();
}

void ASaveManager::Save()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Saved game");
	UMOOSaveGame* SaveGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::CreateSaveGameObject(UMOOSaveGame::StaticClass()));
	SaveGameInstance->Data = SaveDataCandidate;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
	/* TODO: Make sure load doesn't need to be called */
	Load();
}

FSave* ASaveManager::GetData()
{
	return &SaveDataCandidate;
}

void ASaveManager::SetData(FSave Data)
{
	SaveDataCandidate = Data;
}

void ASaveManager::AddActorSave(FActorSave ActorSave)
{
	DeleteActorSave(ActorSave.Id);
	GetData()->Actors.Add(ActorSave);
}

void ASaveManager::DeleteActorSave(FName Id)
{
	TArray<FActorSave> Actors = GetData()->Actors;
	int32 ActorNum = Actors.Num();

	for (int32 b = 0; b < ActorNum; b++)
	{
		if (Actors[b].Id == Id)
		{
			Actors.RemoveAt(b);
			break;
		}
	}
}

FActorSave ASaveManager::GetActorSave(FName Id)
{
	TArray<FActorSave> Actors = GetData()->Actors;
	int32 ActorNum = Actors.Num();

	for (int32 b = 0; b < ActorNum; b++)
	{
		if (Actors[b].Id.IsEqual(Id))
		{
			return Actors[b];
		}
	}

	return FActorSave();
}

void ASaveManager::AddInteractableSave(FInteractableSave InteractableSave)
{
	DeleteInteractableSave(InteractableSave.Id);
	GetData()->Interactables.Add(InteractableSave);
}

void ASaveManager::DeleteInteractableSave(FName Id)
{
	TArray<FInteractableSave> Interactables = GetData()->Interactables;
	int32 InteractableNum = Interactables.Num();

	for (int32 b = 0; b < InteractableNum; b++)
	{
		if (Interactables[b].Id == Id)
		{
			Interactables.RemoveAt(b);
			break;
		}
	}
}

FInteractableSave* ASaveManager::GetInteractableSave(FName Id)
{
	TArray<FInteractableSave> Interactables = GetData()->Interactables;
	int32 InteractableNum = Interactables.Num();

	for (int32 b = 0; b < InteractableNum; b++)
	{
		if (Interactables[b].Id == Id)
		{
			return &Interactables[b];
		}
	}

	return nullptr;
}