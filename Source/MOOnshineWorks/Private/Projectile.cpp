// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Projectile.h"


AProjectile::AProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Use a sphere as a simple collision representation
	CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAll");			// Collision profiles are defined in DefaultEngine.ini
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blockin
	RootComponent = CollisionComp;

	ProjectileMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("projectileMesh"));
	ProjectileMesh->AttachTo(RootComponent);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;

	// Die after 10 seconds by default
	InitialLifeSpan = 10.f;
}


void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
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