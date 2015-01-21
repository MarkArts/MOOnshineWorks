// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_FridgeController.h"
#include "AI_FridgeEnemy.h"


AAI_FridgeController::AAI_FridgeController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void AAI_FridgeController::AttackPlayer()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	//AAI_BasicEnemy* WalkingEnemyzz = (AAI_BasicEnemy*)GetPawn();

	if (AiChar)
	{
		AAI_ChargeEnemy* AiSpecific = Cast<AAI_ChargeEnemy>(GetPawn());
		AMOOnshineWorksCharacter* playerCharacter = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
		if (playerCharacter)
		{
			FRotator EnemyRotation = AiSpecific->GetActorRotation();

			//Pak de x,y van de speler 
			FVector PlayerLocation = playerCharacter->GetActorLocation();
			//Pak de x,y van de Enemy
			FVector AiSpecificLocation = AiSpecific->GetActorLocation();
			//Bereken het verschil van deze waardes -/+ de character om te berekenen welke kant hij op moet!
			FVector difference = PlayerLocation - AiSpecificLocation;

			if (AiSpecific->PushPower >= 0)
			{
				playerCharacter->AddImpulseToCharacter(AiSpecific->PushPower*difference);
			}
			else {
			}
			//Doe Damage
			playerCharacter->DealDamage(AiChar->Damage);
		}
	}
}
void AAI_FridgeController::Patrol()
{
	
}


