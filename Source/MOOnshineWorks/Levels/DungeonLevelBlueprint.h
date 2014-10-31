// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
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


	//===========
	// BP Nodes
	//===========
public:
	/** This triggers a save / update of all the Solus Save Game level data. This should be called before the level is unloaded/unstreamed via blueprints.*/
	//UFUNCTION(BlueprintCallable, Category = "Solus Level Save System")
//		void SolusLevel__UpdateLevelSaveData();


	//OVERRIDES
protected:

	virtual void ReceiveBeginPlay() OVERRIDE;

	//ON REMOVE FROM WORLD - USE INSTEAD OF BEGIN DESTROY
	/** Called when this actor is in a level which is being removed from the world (e.g. my level is getting UWorld::RemoveFromWorld called on it) */
	/*
	virtual void OnRemoveFromWorld() override;
	*/
	//THIS GOT REPLACED BY

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//TICK
protected:

	//Tick
	virtual void Tick(float DeltaSeconds) OVERRIDE;

};
