// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ACollectible : public AActor
{
	GENERATED_BODY()
public:
	ACollectible(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FString UsedText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool ShouldSave;

	UFUNCTION(BluePrintNativeEvent)
	void OnCollect(AActor* Target);
	UFUNCTION(BlueprintCallable, Category=MOO)
	virtual void Collect(AActor* Target);

protected:
	virtual void ReceiveBeginPlay() override;
};
