// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectible.h"
#include "DoorKey.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
namespace EDoorKey
{
	enum Type
	{
		None,
		Red,
		Green,
		Blue
	};
}

UCLASS()
class MOONSHINEWORKS_API ADoorKey : public ACollectible
{
	GENERATED_UCLASS_BODY()

		UFUNCTION(BlueprintCallable, Category = "Moonshine")
		int8 GetKeyName();

		UFUNCTION(BlueprintCallable, Category = "Moonshine")
		FString OnPickedUp();

		UFUNCTION(BlueprintCallable, Category = "Moonshine")
		void SetKeyName(const EDoorKey::Type InsertKey);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moonshine")
		TEnumAsByte<EDoorKey::Type> KeyName;

		virtual void OnCollect_Implementation(AActor* Target) override;
};
