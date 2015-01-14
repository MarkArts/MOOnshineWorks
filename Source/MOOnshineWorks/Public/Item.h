// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AItem : public AActor
{
	GENERATED_BODY()
public:
	AItem(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	FName Name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	float Id;
	
	UFUNCTION(BlueprintNativeEvent, Category = Item)
	void OnUse();

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void Use();
};
