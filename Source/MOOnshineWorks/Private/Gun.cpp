// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Gun.h"


AGun::AGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	GunMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("gunMesh"));
	RootComponent = GunMesh;

	GunOffset = FVector(0.f, 0.f, 100.f);
}

FRotator AGun::GetBulletAngle()
{
	FRotator BulletAngle = GunMesh->GetComponentRotation();
	float RandomRoll = FMath::Rand() * 360.f;
	float RandomYaw = FMath::Rand() * SpreadAngle * 2;
	RandomYaw -= SpreadAngle;
	BulletAngle.Roll += RandomRoll;
	BulletAngle.Yaw = RandomYaw;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("angleshizzle"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(BulletAngle.Roll));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(BulletAngle.Yaw));
	return BulletAngle;
}

void AGun::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew1"));
	if (MagazineLoadCount > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew2"));
		MagazineLoadCount--;
		UWorld* const World = GetWorld();
		FVector SpawnLocation = GetActorLocation() + FVector(100.f, 100.f, 100.f);

		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew3"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[0]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[1]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[2]));
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

	Reloading = false
}