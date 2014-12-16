// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MOOnshineWorksCharacter.h"
#include "Helpers.generated.h"

/**
 * Function to hold 
 */
UCLASS()
class MOONSHINEWORKS_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Helpers)
	static FName GeneratePersistentId(AActor* Actor);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Helpers)
	static ASaveManager* GetSaveManager(UWorld* World);
	UFUNCTION(BlueprintCallable, Category = Helpers)
	static void CreateCheckpoint(AMOOnshineWorksCharacter* Actor);
	UFUNCTION(BlueprintCallable, Category = Helpers)
	static TArray<FName> GetActiveLevelsFrom(UWorld* World);
	//UFUNCTION(BlueprintCallable, Category = Helpers)
	static void DisplayText(UWorld* World, FString Text, FVector2D Position, FColor Color);
};
