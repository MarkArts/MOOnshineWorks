// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Projectile.h"


AProjectile::AProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	ProjectileMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("projectileMesh"));
	ProjectileMesh->SetCollisionProfileName(FName("ProjectileCollisionProfile"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;

	InitialLifeSpan = 1.f;
}

void AProjectile::ReceiveBeginPlay()
{
	if (GetOwner())
	{
		AGun* Gun = Cast<AGun>(GetOwner());
		ProjectileMesh->IgnoreActorWhenMoving(Gun, true);
		if (Gun->GetOwner())
		{
			AMOOnshineWorksCharacter* GunOwner = Cast<AMOOnshineWorksCharacter>(Gun->GetOwner());
			if (GunOwner)
			{
				ProjectileMesh->IgnoreActorWhenMoving(GunOwner, true);
			}
			else
			{
				AAI_BasicEnemy* GunOwner = Cast<AAI_BasicEnemy>(Gun->GetOwner());
				if (GunOwner)
				{
					ProjectileMesh->IgnoreActorWhenMoving(GunOwner, true);
				}
			}
		}
	}
	Super::ReceiveBeginPlay();
}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && (OtherActor != GetOwner()))
	{
		if (GetOwner()->GetOwner())
		{
			if (OtherActor != GetOwner()->GetOwner())
			{
				HitActor(OtherActor);
			}
		}
		else
		{
			HitActor(OtherActor);
		}
	}
	else
	{
		if (!ProjectileMovement->bShouldBounce){
			HitEvent();
			Destroy();
		}
	}
}

void AProjectile::HitEvent_Implementation()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		World->SpawnActor<AActor>(DeathBlueprint, RootComponent->GetComponentLocation(), FRotator::ZeroRotator);
	}
}

void AProjectile::HitActor(AActor* OtherActor)
{
	HitEvent();
	if (OtherActor->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
		AAI_BasicEnemy* TargetEnemy = Cast<AAI_BasicEnemy>(OtherActor);
		if (TargetEnemy)
		{
			TargetEnemy->DealDamage(DamageValue);
		}
	}
	if (OtherActor->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
		AMOOnshineWorksCharacter* TargetPlayer = Cast<AMOOnshineWorksCharacter>(OtherActor);
		if (TargetPlayer)
		{
			TargetPlayer->DealDamage(DamageValue);
		}
	}
	Destroy();
}