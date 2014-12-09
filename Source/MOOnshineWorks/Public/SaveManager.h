// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MOOSaveGame.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASaveManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = MOO)
	FSave SaveData;

	UPROPERTY(VisibleAnywhere, Category = MOO)
	FSave SaveDataCandidate; // Possible Save

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	void Load();
	void ResetData();
	void RemoveSave();
	void Save();
	FSave* GetData();
	void SetData(FSave Data);
	
	void AddActorSave(FActorSave ActorSave);
	void DeleteActorSave(FName Id);
	FActorSave* GetActorSave(FName Id);
};
