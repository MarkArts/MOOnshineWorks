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
		LibraryF1D1,
		LibraryF1D2,
		LibraryF1D3,
		LibraryF1D4,
		LibraryF1D5,
		LibraryF1D6,
		LibraryF1D7,
		LibraryF2D1,
		LibraryF2D2,
		LibraryF2D3,
		LibraryF2D4,
		LibraryF2D5,
		LibraryF2D6,
		LibraryF3E1
	};
}

UCLASS()
class MOONSHINEWORKS_API ADoorKey : public ACollectible
{
	GENERATED_BODY()
public:
	ADoorKey(const class FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	EDoorKey::Type GetKeyName();

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	FString OnPickedUp();

	UFUNCTION(BlueprintCallable, Category = "Moonshine")
	void SetKeyName(const EDoorKey::Type InsertKey);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moonshine")
	TEnumAsByte<EDoorKey::Type> KeyName;

	virtual void OnCollect_Implementation(AActor* Target) override;
};
