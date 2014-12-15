// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Changeable.h"


AChangeable::AChangeable(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AChangeable::Activate_Implementation()
{
	Change();
}

void AChangeable::Change()
{
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoCollisionFail = true;
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(TargetClass, GetActorLocation(), GetActorRotation(), SpawnParameters);

	if (Pawn)
	{
		if (Pawn->Controller)
		{
			Pawn->SpawnDefaultController();
		}
		if (BehaviorTree != NULL)
		{
			AAIController* AIController = Cast<AAIController>(Pawn->Controller);
			if (AIController != NULL)
			{
				AIController->RunBehaviorTree(BehaviorTree);
			}
		}
	}

	Destroy();
}