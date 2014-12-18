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
}

void AExplosion::ReceiveBeginPlay()
{
	TArray<AActor*> Items;
	EffectSphere->GetOverlappingActors(Items);
	for (AActor* Item : Items)
	{
		if (Item->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
		{
			AMOOnshineWorksCharacter* Target = Cast<AMOOnshineWorksCharacter>(Item);
			if (Target)
			{
				Target->DealDamage(DamageValue);
			}
		}
		else if (Item->GetClass()->IsChildOf(AAI_BasicEnemy::StaticClass()))
		{
			AAI_BasicEnemy* Target = Cast<AAI_BasicEnemy>(Item);
			if (Target)
			{
				Target->DealDamage(DamageValue);
			}
		}
	}
	Destroy();
}

