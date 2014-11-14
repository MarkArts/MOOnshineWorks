// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Gun.h"


AGun::AGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	gunMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("gunMesh"));
	RootComponent = gunMesh;

	gunOffset = FVector(0.f, 0.f, 100.f);
}

FRotator AGun::getBulletAngle()
{
	FRotator bulletAngle = gunMesh->GetComponentRotation();
	float randomRoll = FMath::Rand() * 360.f;
	float randomYaw = FMath::Rand() * spreadAngle * 2;
	randomYaw -= spreadAngle;
	bulletAngle.Roll += randomRoll;
	bulletAngle.Yaw = randomYaw;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("angleshizzle"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(bulletAngle.Roll));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(bulletAngle.Yaw));
	return bulletAngle;
}

void AGun::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew1"));
	if (magazineLoadCount > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew2"));
		magazineLoadCount--;
		UWorld* const world = GetWorld();
		FVector SpawnLocation = GetActorLocation() + FVector(100.f, 100.f, 100.f);

		if (world != NULL)
		{
			// spawn the projectile at the muzzle
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew3"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[0]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[1]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[2]));
			world->SpawnActor<AProjectile>(projectileClass, SpawnLocation, getBulletAngle());
		}
	}
	else
	{
		reload();
	}
}

void AGun::onReload_Implementation()
{
	
}

void AGun::reload()
{
	reloading = true;
	//delay
	magazineLoadCount = magazineCapacity;

	reloading = false;
	onReload();
}