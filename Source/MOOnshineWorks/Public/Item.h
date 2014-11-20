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
	FString Name;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	float Id;
	
	UFUNCTION(BlueprintNativeEvent, Category = Item)
	void OnUse();

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void Use();

};
