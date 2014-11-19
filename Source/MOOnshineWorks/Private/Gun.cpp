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
	BulletAngle.Pitch += (FMath::FRandRange(0,1) * SpreadAngle) - (SpreadAngle / 2);
	BulletAngle.Roll += (FMath::FRand() * 360.f);
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
		//Enemies don't have cameras, catch this
		
		if (World != NULL)
		{
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

/*FVector AGun::GetPlayerOrientation()
{
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	UCameraComponent* Camera = Owner->FollowCamera;
	FMinimalViewInfo ViewInfo = FMinimalViewInfo();
	Camera->GetCameraView(0.f, ViewInfo);

	FVector Location = ViewInfo.Location;
	FVector Rotation = ViewInfo.Rotation.Vector();

	FVector End = Location + Rotation * FVector(5000.f, 5000.f, 5000.f);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = false;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingle(
		RV_Hit,        //result
		Location,    //start
		End, //end
		ECC_MAX, //collision channel
		RV_TraceParams
		))
	{
		return RV_Hit.Location;
	}
	//return NULL;
}*/