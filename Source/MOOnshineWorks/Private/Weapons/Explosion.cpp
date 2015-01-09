// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicEnemy.h"
#include "Explosion.h"


AExplosion::AExplosion(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	EffectSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("EffectSphere"));
	EffectSphere->SetCollisionProfileName("ExplosionCollisionProfile");
	RootComponent = EffectSphere;
}

void AExplosion::ReceiveBeginPlay()
{
	EffectSphere->SetSphereRadius(EffectRadius);
	Super::ReceiveBeginPlay();
	Explode();
}

void AExplosion::Explode()
{
	TArray<AActor*> Items;
	EffectSphere->GetOverlappingActors(Items);
	for (AActor* Item : Items)
	{
		if (Item->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()) || Item->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
		{
			Hit(Item);
		}
	}
}

void AExplosion::Hit(AActor* Target)
{
	AMOOnshineWorksCharacter* CharacterTarget = Cast<AMOOnshineWorksCharacter>(Target);
	if (CharacterTarget)
	{
		CharacterTarget->DealDamage(DamageValue);
		CharacterTarget->StartShake(ExplosionShaker);
		if (PushbackSpeed > 0.f)
		{
			FVector ExplosionLoc = GetActorLocation();
			FVector TargetLoc = CharacterTarget->GetActorLocation();
			FVector Direction = TargetLoc - ExplosionLoc;
			CharacterTarget->AddImpulseToCharacter(PushbackSpeed * Direction);
		}
	}
	AAI_BasicEnemy* EnemyTarget = Cast<AAI_BasicEnemy>(Target);
	if (EnemyTarget)
	{
		EnemyTarget->DealDamage(DamageValue);
		if (PushbackSpeed > 0.f)
		{
			FVector ExplosionLoc = GetActorLocation();
			FVector TargetLoc = EnemyTarget->GetActorLocation();
			FVector Direction = TargetLoc - ExplosionLoc;
			EnemyTarget->AddImpulseToEnemy(PushbackSpeed * Direction);
		}
	}
}
