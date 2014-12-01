// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Projectile.h"


AProjectile::AProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Use a sphere as a simple collision representation
	

	ProjectileMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("projectileMesh"));
	ProjectileMesh->SetCollisionProfileName(FName("ProjectileCollisionProfile"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;

	InitialLifeSpan = 1.f;
}


void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitEvent();
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherActor->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
			AAI_BasicEnemy* TargetEnemy = Cast<AAI_BasicEnemy>(OtherActor);
			if (TargetEnemy)
			{
				TargetEnemy->DealDamage(DamageValue);
				Destroy();
			}
		}
		if (OtherActor->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
			AMOOnshineWorksCharacter* TargetPlayer = Cast<AMOOnshineWorksCharacter>(OtherActor);
			if (TargetPlayer)
			{
				TargetPlayer->DealDamage(DamageValue);
				Destroy();
			}
		}
	}

	if (!ProjectileMovement->bShouldBounce){
		Destroy();
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