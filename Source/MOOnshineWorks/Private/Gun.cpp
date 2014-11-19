// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Gun.h"


AGun::AGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	GunMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("gunMesh"));
	RootComponent = GunMesh;

	GunOffset = FVector(50.f, 0.f, 40.f);
}

FRotator AGun::GetBulletAngle()
{
	FRotator BulletAngle = GunMesh->GetComponentRotation();
	/*float RandomRoll = FMath::Rand() * 360.f;
	float RandomYaw = FMath::Rand() * SpreadAngle * 2;
	RandomYaw -= SpreadAngle;
	BulletAngle.Roll += RandomRoll;
	BulletAngle.Yaw = RandomYaw;*/

	return BulletAngle;
}

void AGun::Use()
{
	if (MagazineLoadCount > 0)
	{
		AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
		FRotator OwnerRotation = Owner->GetControlRotation();
		MagazineLoadCount--;
		UWorld* const World = GetWorld();
		FVector SpawnLocation = GetActorLocation() + OwnerRotation.RotateVector(GunOffset);

		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, GetBulletAngle());
			Projectile->DamageValue = DamageValue;
			Super::Use();
		}
	}
	else
	{
		Reload();
	}
}

void AGun::OnReload_Implementation()
{
	
}

void AGun::Reload()
{
	Reloading = true;
	OnReload();
	//delay
	MagazineLoadCount = MagazineCapacity;

	Reloading = false;
}