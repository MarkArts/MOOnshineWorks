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
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float DamageValue;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
	void HitEvent();
	virtual void HitActor(AActor* OtherActor);
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<AActor> DeathBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<AActor> HitBlueprint;
protected:
	virtual void ReceiveBeginPlay() override;
};
