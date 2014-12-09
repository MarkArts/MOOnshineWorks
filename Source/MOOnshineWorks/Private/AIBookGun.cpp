// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AIBookGun.h"


AAIBookGun::AAIBookGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "AIBookGun";
	Id = 14.f;
	
	GunSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("GunSphere"));
	RootComponent = GunSphere;

	SpreadAngle = 0.f;
	ShootCooldown = 0.1f;
}
void AAIBookGun::Use()
{
	if (CanShoot())
	{
		Shoot();
		SetLastShotTime();
	}
}
void AAIBookGun::Shoot()
{
	FVector SpawnLocation = GetActorLocation();

	AProjectile* Projectile = SpawnProjectile(SpawnLocation, GetTarget());
	OnUse();
}

FVector AAIBookGun::GetTarget()
{
	return GetEnemyTarget();
}