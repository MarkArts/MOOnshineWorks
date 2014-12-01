// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Gun.h"


AGun::AGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	GunMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("gunMesh"));
	RootComponent = GunMesh;
	GunMesh->SetCollisionProfileName("OverlapAll");
	LastShot = FDateTime::Now() - FTimespan::FromHours(1);
	GunOffset = FVector(80.f, 0.f, 40.f);
}

FRotator AGun::GetBulletAngle(FVector Start, FVector Target)
{
	FRotator OffsetAngle = FRotator::ZeroRotator;
	OffsetAngle.Pitch += (FMath::FRandRange(0, 1) * SpreadAngle) - (SpreadAngle / 2);
	OffsetAngle.Yaw += (FMath::FRandRange(0, 1) * SpreadAngle) - (SpreadAngle / 2);
	FVector Direction = Target - Start;
	OffsetAngle = OffsetAngle.Add(Direction.Rotation().Pitch, Direction.Rotation().Yaw, 0);
	return OffsetAngle;
}

void AGun::Use()
{
	Shoot();
}

void AGun::Shoot()
{
	FVector SpawnLocation = RootComponent->GetSocketLocation("BulletSpawn");
	AProjectile* Projectile = SpawnProjectile(SpawnLocation, GetTarget());
	OnUse();
}

AProjectile* AGun::SpawnProjectile(FVector Start, FVector End)
{
	AProjectile* Result = NULL;
	UWorld* const World = GetWorld();
	if (World){

		if (RootComponent->DoesSocketExist("BulletSpawn"))
		{
			Result= World->SpawnActor<AProjectile>(ProjectileClass, Start, GetBulletAngle(Start, End));
			Result->DamageValue = DamageValue;
		}
	}
	return Result;
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

bool AGun::HasAmmo()
{
	return true; //MagazineLoadCount > 0;
}

bool AGun::CanShoot()
{
	return FDateTime::Now() - LastShot >= FTimespan::FromSeconds(ShootCooldown);
}

void AGun::SetLastShotTime()
{
	LastShot = FDateTime::Now();
}

void AGun::MagazineCountDecrement()
{
	//MagazineLoadCount = FMath::Max(0.f, MagazineLoadCount - 1);
}

FVector AGun::GetTarget()
{
	APawn* Owner = Cast<APawn>(GetOwner());
	if (Owner->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
	{
		return GetPlayerTarget();
	}
	if (Owner->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
	{
		return GetEnemyTarget();
	}
	return FVector::ZeroVector;
}

FVector AGun::GetEnemyTarget()
{
	AAI_BasicEnemy* Owner = Cast<AAI_BasicEnemy>(GetOwner());
	AAI_BasicController* OwnerController = Cast<AAI_BasicController>(Owner->Controller);
	return OwnerController->BlackboardComp->GetValueAsVector(OwnerController->EnemyLocationID);
}

FVector AGun::GetPlayerTarget()
{
	AMOOnshineWorksCharacter* Owner = Cast<AMOOnshineWorksCharacter>(GetOwner());
	UCameraComponent* Camera = Owner->FollowCamera;
	FMinimalViewInfo ViewInfo = FMinimalViewInfo();
	Camera->GetCameraView(0.f, ViewInfo);

	FVector Location = ViewInfo.Location;
	FVector Rotation = ViewInfo.Rotation.Vector();

	FVector End = Location + Rotation * FVector(5000.f, 5000.f, 5000.f);
	FVector Result = End;

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	//Re-initialize hit info
	FHitResult RV_Hit(EForceInit::ForceInit);
	bool bPawnHit = false;
	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingle(
		RV_Hit,        //result
		Location,    //start
		End, //end
		ECollisionChannel::ECC_Pawn, //collision channel
		RV_TraceParams
		))
	{
		Result = RV_Hit.Location;
		if(!LocationBehindOwner(Result))
		{
			bPawnHit = true;
		}
		else
		{
			Result = End;
		}
	}
	if (!bPawnHit && GetWorld()->LineTraceSingle(
		RV_Hit,        //result
		Location,    //start
		End, //end
		ECollisionChannel::ECC_MAX, //collision channel
		RV_TraceParams
		))
	{
		Result = RV_Hit.Location;
	}
	return Result;
}

bool AGun::LocationBehindOwner(FVector Location)
{
	APawn* Owner = Cast<APawn>(GetOwner());
	FVector OwnerLocation = Owner->GetActorLocation();
	FRotator OwnerRotation = Owner->GetActorRotation();
	bool Result = true;
	if (OwnerRotation.UnrotateVector(OwnerLocation).X < OwnerRotation.UnrotateVector(Location).X)
	{
		Result = false;
	}
	return Result;
}