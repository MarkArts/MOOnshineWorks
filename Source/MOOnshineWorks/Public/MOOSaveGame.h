// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Gun.h"
#include "MOOSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FActorSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool StopSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FVector Postition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FRotator Rotation;
};

USTRUCT(BlueprintType)
struct FCheckPointSave{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<FName> StreamingLevels;
};

USTRUCT(BlueprintType)
struct FPlayerSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FRotator Rotation;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	//TArray<AGun*> Weapons;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
//	TArray<TEnumAsByte<EGunType::Type>> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<FName> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<int32> AmmoCounters;
};

USTRUCT(BlueprintType)
struct FInteractableSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool IsUsed;
};

USTRUCT(BlueprintType)
struct FSave{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<FActorSave> Actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<FInteractableSave> Interactables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FCheckPointSave Checkpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
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