// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableEvent_FOnInteract, AInteractable*, Interactable);

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AInteractable : public AActor
{
	GENERATED_BODY()
public:
	AInteractable(const class FObjectInitializer& PCIP);

	UPROPERTY(BlueprintAssignable, Category = MOO)
	FBindableEvent_FOnInteract OnInteractDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FString DisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FString UsedText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool IsUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool ShouldUseOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	bool StopSpawnWhenUsed;

	UFUNCTION(BluePrintNativeEvent, Category = MOO)
	void OnInteract(AActor* Target);
	UFUNCTION(BlueprintCallable, Category = MOO)
	virtual void Interact(AActor* Target);

	UFUNCTION(BluePrintNativeEvent, Category = MOO)
	void OnInRange(AActor* Target);
	UFUNCTION(BlueprintCallable, Category = MOO)
	virtual void InRange(AActor* Target);

protected:
	virtual void ReceiveBeginPlay() override;
};
