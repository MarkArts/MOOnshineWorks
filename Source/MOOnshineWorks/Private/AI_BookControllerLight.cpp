// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_BookControllerLight.h"
#include "AI_BasicController.h"
#include "AI_BookEnemyLight.h"


AAI_BookControllerLight::AAI_BookControllerLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AAI_BookControllerLight::GoBackToOriginalPosition()
{
	LostPlayer();
	FVector MyLoc = BlackboardComp->GetValueAsVector(OriginalPosition);
	BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
}

void AAI_BookControllerLight::BookPatrol()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	AAI_BasicEnemy* BaseEnemy = (AAI_BasicEnemy*)GetPawn();
	BaseEnemy->StartSprint();
	FVector MyLoc = MyBot->GetActorLocation();
	
	float AddX; ////// WhereShouldAIPatrolTo
	float AddY;
	float WhereShouldAIPatrolToFloat = BlackboardComp->GetValueAsFloat(WhereShouldAIPatrolTo);
	float NewWhereShouldAIPatrolTo;

	//Check de huidige waarde van WhereShouldAIPatrolTo
	if (WhereShouldAIPatrolToFloat == 0)
	{
		AddX = 500;
		AddY = 500;
		NewWhereShouldAIPatrolTo = 1;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	} 
	else if (WhereShouldAIPatrolToFloat == 1)
	{
		AddX = 500;
		AddY = -500;
		NewWhereShouldAIPatrolTo = 2;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	else if (WhereShouldAIPatrolToFloat == 2)
	{
		AddX = -500;
		AddY = -500;
		NewWhereShouldAIPatrolTo = 3;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	else if (WhereShouldAIPatrolToFloat == 3)
	{
		AddX = -500;
		AddY = 500;
		NewWhereShouldAIPatrolTo = 0;

		BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(NewWhereShouldAIPatrolTo));
	//Pas de WhereShouldAIPatrolTo nummer aan zodat die een andere kant op loopt volgende keer

	//Pas de locatie waar de AI moet heen lopen aan en stuur deze naar het Blackboard
	float NewX = MyLoc[0] + AddX;
	float NewY = MyLoc[1] + AddY;
	MyLoc.Set(NewX, NewY, MyLoc[2]);
	BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
}

void AAI_BookControllerLight::BookAttackPlayer()
{
	//Op de speler gaan schieten indien die in zicht is!!
}
