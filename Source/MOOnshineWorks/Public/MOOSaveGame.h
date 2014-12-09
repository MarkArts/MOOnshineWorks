// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "MOOSaveGame.generated.h"

USTRUCT()
struct FActorSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FName Id;
	UPROPERTY()
	bool StopSpawn;
	UPROPERTY()
	FTransform Transform;
};

USTRUCT()
struct FCheckPointSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FTransform TransForm;
	UPROPERTY()
	FName StreamingLevel;
};

USTRUCT()
struct FPlayerSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FCheckPointSave Checkpoint;
	UPROPERTY()
	FTransform Transform;
};

USTRUCT()
struct FSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	TArray<FActorSave> Actors;

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