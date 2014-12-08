// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "Item.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AGun : public AItem
{
	GENERATED_UCLASS_BODY()

	FVector CharacterEquipOffset;
	FRotator CharacterEquipRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float ShootCooldown;
	FDateTime LastShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float SpreadAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gun)
	TSubobjectPtr<UStaticMeshComponent> GunMesh;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	FVector GunOffset;

	virtual void Use() override; 
	
	UFUNCTION(BlueprintCallable, Category = Bullet)
	FRotator GetBulletAngle(FVector Start, FVector Target);

	virtual FVector GetTarget();
	FVector GetPlayerTarget();
	FVector GetEnemyTarget();
	bool LocationBehindBulletSpawn(FVector Location);
	virtual bool CanShoot();
	void SetLastShotTime();
	virtual void Shoot();
	AProjectile* SpawnProjectile(FVector Start, FVector End);
	virtual TSubclassOf<class AProjectile> GetProjectileClass();

};
