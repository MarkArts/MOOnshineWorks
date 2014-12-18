// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AExplosion : public AActor
{
	GENERATED_UCLASS_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MOOnshine)
	TSubobjectPtr<USphereComponent> EffectSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Radius)
	float EffectRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Radius)
	float DamageValue;

	virtual void ReceiveBeginPlay() override;
};
