// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_BasicEnemy.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubobjectPtr<UStaticMeshComponent> ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float DamageValue;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
	void HitEvent();
	virtual void HitActor(AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<AActor> DeathBlueprint;
protected:
	virtual void ReceiveBeginPlay() override;
};
