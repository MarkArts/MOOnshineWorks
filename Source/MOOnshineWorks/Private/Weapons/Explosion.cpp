// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicEnemy.h"
#include "Explosion.h"


AExplosion::AExplosion(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	EffectSphere= PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("EffectSphere"));
	EffectSphere->SetSphereRadius(EffectRadius);
	RootComponent = EffectSphere;
}

//void AExplosion::ReceiveBeginPlay()
//{
//	Super::ReceiveBeginPlay();
//	Explode();
//}

void AExplosion::Explode()
{
	//TArray<AActor*> Items;
	//GetOverlappingActors(Items);
	for (AActor* Item : OverlappingActors)
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
	}
	AAI_BasicEnemy* EnemyTarget = Cast<AAI_BasicEnemy>(Target);
	if (EnemyTarget)
	{
		EnemyTarget->DealDamage(DamageValue);
	}
}
