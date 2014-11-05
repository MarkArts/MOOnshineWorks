// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "Engine/LevelStreaming.h"
#include "DungeonLevelBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ADungeonLevelBlueprint : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moonshine)
	TArray<uint8> SubLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moonshine)
	FString CurrentLevel;


	//===========
	// BP Nodes
	//===========
public:

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void LoadLevel(FName TargetLevel, FString UniqueName);

	//OVERRIDES
protected:

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void UnloadCurrentLevel();

	virtual void ReceiveBeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//TICK
protected:

	//Tick
	virtual void Tick(float DeltaSeconds) override;

};
