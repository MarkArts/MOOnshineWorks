// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pistol.h"


APistol::APistol(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Name = "Pistol";
	Id = 14.f;

	/*static ConstructorHelpers::FClassFinder<AProjectile> BP_Projectile(TEXT("/Game/Blueprints/BP_Projectile"));
	ProjectileClass = BP_Projectile.Class;*/

	MagazineCapacity = 15.f;
	MagazineLoadCount = MagazineCapacity;
	DamageValue = 5.f;
	ReloadTime = 2.f;
	SpreadAngle = 0.f;
	Reloading = false;
}

void APistol::ReceiveBeginPlay()
{
	AMOOnshineWorksGameMode* GameMode = Cast<AMOOnshineWorksGameMode>(GetWorld()->GetAuthGameMode());

	ProjectileClass =  TSubclassOf<AProjectile>(*(BlueprintLoader::Get().GetBP("BP_Projectile")));
	Super::ReceiveBeginPlay();
}

