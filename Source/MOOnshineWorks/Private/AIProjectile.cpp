// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AIProjectile.h"


AAIProjectile::AAIProjectile(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}
/*
void AAIProjectile::HitActor(AActor* OtherActor)
{
	if (OtherActor->GetClass()->IsChildOf(AMOOnshineWorksCharacter::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
		AMOOnshineWorksCharacter* TargetPlayer = Cast<AMOOnshineWorksCharacter>(OtherActor);
		if (TargetPlayer)
		{
			HitEvent();
			TargetPlayer->DealDamage(DamageValue);
		}
	}
	Destroy();
}
*/