// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BookEnemyLight.h"
#include "AI_BookControllerLight.h"


AAI_BookEnemyLight::AAI_BookEnemyLight(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AAI_BookControllerLight::StaticClass();

	Health = 3.f;
	Defense = 0.f;
	Speed = 1.2f;
}
void AAI_BookEnemyLight::ReceiveBeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	if (GunClass)
	{ 
		Gun = GetWorld()->SpawnActor<AAIBookGun>(GunClass, SpawnParams);
		Gun->SetActorLocation(GetMesh()->GetComponentLocation());
		Gun->AttachRootComponentTo(GetMesh());
	}
	Super::ReceiveBeginPlay();
}


