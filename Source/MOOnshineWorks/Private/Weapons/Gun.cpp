// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Gun.h"


AGun::AGun(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	GunMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("gunMesh"));
	RootComponent = GunMesh;

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
	if (MagazineLoadCount > 0)
	{
		APawn* Owner = Cast<APawn>(GetOwner());
		FRotator OwnerRotation = Owner->GetControlRotation();
		MagazineLoadCount--;
		UWorld* const World = GetWorld();
		FVector SpawnLocation = GetActorLocation() + OwnerRotation.RotateVector(GunOffset);
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//Enemies don't have cameras, catch this
		FVector Target = FVector::ZeroVector;
		if (Owner->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
		{
			Target = GetPlayerTarget();
		}
		if (Owner->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
		{
			Target = GetEnemyTarget();
		}
		if (World != NULL)
		{
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, GetBulletAngle(SpawnLocation, Target));
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
	return End;
}