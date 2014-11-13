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
	float magazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float magazineLoadCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float damageValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float reloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float spreadAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gun)
	bool reloading;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gun)
	TSubobjectPtr<UStaticMeshComponent> gunMesh;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	TSubclassOf<class AProjectile> projectileClass;


	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	FVector gunOffset;

	virtual void activate(FRotator controlRotation) override;
	
	UFUNCTION(BlueprintCallable, Category = Bullet)
	FRotator getBulletAngle();

	UFUNCTION(BlueprintNativeEvent)
	void onReload();

	UFUNCTION()
	void reload();
};
