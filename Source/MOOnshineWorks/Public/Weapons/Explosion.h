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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Explosion)
	USphereComponent* EffectSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float EffectRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float DamageValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	bool DoesPushback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float PushbackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> ExplosionShaker;

	UFUNCTION(BlueprintCallable, Category = Explosion)
	void Explode();
	void Hit(AActor* Target);

protected:
	virtual void ReceiveBeginPlay() override;
};
