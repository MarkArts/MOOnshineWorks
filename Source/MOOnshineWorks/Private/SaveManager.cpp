// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "SaveManager.h"

ASaveManager::ASaveManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	SaveSlotName = TEXT("TestSaveSlot");
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
	ResetData();
}

void ASaveManager::Save()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Saved game");
	UMOOSaveGame* SaveGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::CreateSaveGameObject(UMOOSaveGame::StaticClass()));
	SaveGameInstance->Data = SaveDataCandidate;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
}

FSave ASaveManager::GetData()
{
	return SaveDataCandidate;
}

void ASaveManager::SetData(FSave Data)
{
	SaveDataCandidate = Data;
}