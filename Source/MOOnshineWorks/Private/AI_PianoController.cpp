// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"
#include "AI_PianoController.h"
#include "AI_PianoEnemy.h"


AAI_PianoController::AAI_PianoController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}
void AAI_PianoController::AttackPlayer()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if (AiChar)
	{
		AAI_PianoEnemy* AiSpecific = Cast<AAI_PianoEnemy>(GetPawn());
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
			if (playerCharacter)
			{
				FVector PlayerLocation = playerCharacter->GetActorLocation();
				playerCharacter->DealDamage(AiChar->Damage);

				FRotator EnemyRotation = AiSpecific->GetActorRotation();
				if (EnemyRotation.UnrotateVector(PlayerLocation).X < EnemyRotation.UnrotateVector(PlayerLocation).X)
				{
					//nog niet af!!!
					playerCharacter->LaunchCharacter(AiSpecific->PianoPushBack, true, false);
				}
			}
		}
	}
}
void AAI_PianoController::SpeedUp()
{

}
void AAI_PianoController::PianoPatrol()
{
	
}

