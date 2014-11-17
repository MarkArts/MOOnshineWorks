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

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TSubobjectPtr<class USphereComponent> CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubobjectPtr<UStaticMeshComponent> ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float DamageValue;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float InitialSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	bool RotationFollowsVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	bool ShouldBounce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float GravityScale;
	*/

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
