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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float MagazineLoadCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float DamageValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float SpreadAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gun)
	bool Reloading;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gun)
	TSubobjectPtr<UStaticMeshComponent> GunMesh;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	FVector GunOffset;

	virtual void Use() override;
	
	UFUNCTION(BlueprintCallable, Category = Bullet)
	FRotator GetBulletAngle(FVector Start, FVector Target);

	UFUNCTION(BlueprintNativeEvent, Category = Gun)
	void OnReload();

	UFUNCTION(BlueprintCallable, Category = Gun)
	void Reload();

	FVector GetPlayerTarget();
	FVector GetEnemyTarget();
	bool LocationBehindOwner(FVector Location);
};
