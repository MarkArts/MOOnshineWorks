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
	UMOOSaveGame* LoadGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::CreateSaveGameObject(UMOOSaveGame::StaticClass()));
	LoadGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	SaveData = LoadGameInstance->Data;
	Reset();
}
void ASaveManager::Reset()
{
	SaveDataCandidate = SaveData;
}
void ASaveManager::Save()
{
	UMOOSaveGame* SaveGameInstance = Cast<UMOOSaveGame>(UGameplayStatics::CreateSaveGameObject(UMOOSaveGame::StaticClass()));
	SaveGameInstance->Data = SaveDataCandidate;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
}
FSave ASaveManager::GetData()
{
	return SaveData;
}
