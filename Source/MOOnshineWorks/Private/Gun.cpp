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
	float randomYaw = FMath::Rand() * 360.f;
	float randomPitch = FMath::Rand() * spreadAngle * 2;
	randomPitch -= spreadAngle;
	bulletAngle.Yaw += randomYaw;
	bulletAngle.Pitch = randomPitch;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("angleshizzle"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(bulletAngle.Yaw));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(bulletAngle.Pitch));
	return bulletAngle;
}

void AGun::activate(FRotator controlRotation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew1"));
	if (magazineLoadCount > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew2"));
		magazineLoadCount--;
		UWorld* const world = GetWorld();
		FVector SpawnLocation = GetActorLocation() + controlRotation.RotateVector(gunOffset);
		if (world != NULL)
		{
			// spawn the projectile at the muzzle
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pew3"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[0]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[1]));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(SpawnLocation[2]));
			world->SpawnActor<AProjectile>(AProjectile::StaticClass(), SpawnLocation, getBulletAngle());
		}
	}
	else
	{
		reload();
	}
	Super::activate(controlRotation);
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