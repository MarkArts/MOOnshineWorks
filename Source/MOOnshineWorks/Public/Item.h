// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AItem : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	FString name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	float id;

	UFUNCTION(BlueprintNativeEvent)
	void onActivate();
	
	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void activate(FRotator controlRotation);
};
