// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DebuffManager.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ADebuffManager : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	virtual void SetDebuff(AActor* Target);

	virtual void QuitDebuff();

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void StartDebuff(ADebuffManager* Target, AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, Category = MOOnshine)
	void OnSetDebuff(AActor* Target);

	bool IsValid(ADebuffManager* nameDebuff);

	void SetTime(float Time);

	//virtual void Start(ADebuffManager* Target);

	bool Repeat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	FString DebuffType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	float DebuffTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOOnshineWorks)
	TArray<ADebuffManager*> DebuffsActive;
	
};
