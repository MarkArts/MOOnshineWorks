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
		LibraryF3E1,
		KitchenF3D1,
		KitchenLobby,
		LobbyBasement,
		BasementF1D1,
		BasementF1D2,
		BasementF1D3,
		BasementF1D4,
		BasementF1D5,
		BasementF1D6,
		BasementF1D7,
		BasementF1D8,
		BasementF2D1,
		BasementF2D2,
		BasementF2D3,
		BasementF2D4,
		BasementF2D5,
		BasementF2D6,
		BasementF2D7,
		BasementF2D8,
		BasementF3D1,
		BasementF3D2,

		// Deprecated but left in because its still referenced
		Red,
		Blue,
		Green
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
	void SetKeyName(const EDoorKey::Type InsertKey);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moonshine")
	TEnumAsByte<EDoorKey::Type> KeyName;

	virtual void Collect(AActor* Target) override;
	virtual void OnCollect_Implementation(AActor* Target) override;
};
