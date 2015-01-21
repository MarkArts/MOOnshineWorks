// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "Item.h"
#include "Gun.generated.h"

UENUM(BlueprintType, Category = Guns)
namespace EGunType
{
	enum Type
	{
		None,
		Crossbow,
		Shotgun,
		Bazooka
	};
}

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AGun : public AItem
{
	GENERATED_BODY()
public:
	AGun(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float ShootCooldown;
	float LastShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float SpreadAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun)
	TEnumAsByte<EGunType::Type> Type;

	//UPROPERTY(VisibleAnywhere, Category = Gun)
	//TSubobjectPtr<class USkeletalMeshComponent> GunMesh;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
	FVector GunOffset;

	//virtual void Use() override; 
	
	UFUNCTION(BlueprintCallable, Category = Bullet)
	FRotator GetBulletAngle(FVector Start, FVector Target);

	//FVector GetTarget();
	FVector GetPlayerTarget();
	//FVector GetEnemyTarget();
	bool LocationBehindBulletSpawn(FVector Location);
	virtual bool CanShoot();
	void SetLastShotTime();
	//virtual void Shoot();
	AProjectile* SpawnProjectile(FVector Start, FVector End);
	virtual TSubclassOf<class AProjectile> GetProjectileClass();


	//charge stuff
	virtual bool CanCharge();
	virtual void StartCharge();
	virtual void EndCharge();
	virtual void StopCharge();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, Category = Charge)
	void OnStartCharge();
	UFUNCTION(BlueprintNativeEvent, Category = Charge)
	void OnEndCharge();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Charge)
	bool IsCharging;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Charge)
	float Charge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Charge)
	float ChargeRatePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Charge)
	float ChargeMultiplier;
};
