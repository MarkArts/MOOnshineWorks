// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "ActivateAI.h"


AActivateAI::AActivateAI(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AActivateAI::Activate()
{
	Change();
}

void AActivateAI::Change()
{

	FActorSpawnParameters SpawnPars = FActorSpawnParameters();
	SpawnPars.bNoCollisionFail = false;

	GetWorld()->SpawnActor<APawn>(SpawnClass, GetActorLocation(), GetActorRotation(), SpawnPars);
	Destroy();
}


