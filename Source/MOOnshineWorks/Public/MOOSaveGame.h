// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MOOSaveGame.generated.h"

USTRUCT()
struct FEnemySave{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName Id;
	UPROPERTY()
	FVector Location;
	UPROPERTY()
	FRotator Rotation;
	UPROPERTY()
	int8 State;

};

USTRUCT()
struct FPlayerSave{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int8 Level; // desingers will be freaking i they see this man :D
	UPROPERTY()
	FVector Position;
	UPROPERTY()
	FRotator Rotation;
};


/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API UMOOSaveGame : public USaveGame
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = MOO)
	TArray<FEnemySave> Enemies;

	UPROPERTY(VisibleAnywhere, Category = MOO)
	FPlayerSave Player;

};