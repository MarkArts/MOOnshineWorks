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

	UPROPERTY(BlueprintReadWrite, Category = MOO)
	FSave SaveDataCandidate; // Possible Save

	UPROPERTY(BlueprintReadWrite, Category = MOO)
	FString SaveSlotName;
	UPROPERTY(BlueprintReadWrite, Category = MOO)
	uint32 UserIndex;

	UFUNCTION(BlueprintCallable, Category = MOO)
	void Load();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void ResetData();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void RemoveSave();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void Save();
	// UFUNCTION(BlueprintCallable, Category = MOO)
	FSave* GetData();
	UFUNCTION(BlueprintCallable, Category = MOO)
	void SetData(FSave Data);
	
	UFUNCTION(BlueprintCallable, Category = MOO)
	void AddActorSave(FActorSave ActorSave);
	UFUNCTION(BlueprintCallable, Category = MOO)
	void DeleteActorSave(FName Id);
	// UFUNCTION(BlueprintCallable, Category = MOO)
	FActorSave* GetActorSave(FName Id);
};
