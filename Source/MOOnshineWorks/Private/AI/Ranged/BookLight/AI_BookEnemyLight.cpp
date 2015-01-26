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
	WalkSpeed = 0.f;
}
void AAI_BookEnemyLight::ReceiveBeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	// Added GetMesh check becuase it randomly crashe dhere. No idea if this will fix anything and should be found out
	if (GunClass && GetMesh())
	{ 
		Gun = GetWorld()->SpawnActor<AGun>(GunClass, SpawnParams);
		if (Gun)
		{
			Gun->SetActorLocation(GetMesh()->GetComponentLocation());
			Gun->AttachRootComponentTo(GetMesh());
		}
	}
	Super::ReceiveBeginPlay();
}


