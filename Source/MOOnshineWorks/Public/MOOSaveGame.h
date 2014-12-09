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
	bool Death;
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

USTRUCT()
struct FSave{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	TArray<FEnemySave> Enemies;

	UPROPERTY()
	FPlayerSave Player;
};

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API UMOOSaveGame : public USaveGame
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = MOO)
	FSave Data;
};