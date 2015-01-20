// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_RangeController.h"


AAI_RangeController::AAI_RangeController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AAI_RangeController::GoBackToOriginalPosition()
{
	/*
	LostPlayer();
	FVector MyLoc = BlackboardComp->GetValueAsVector(OriginalPosition);
	BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
	*/
}

void AAI_RangeController::Patrol()
{
	/*
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	AAI_BasicEnemy* BaseEnemy = (AAI_BasicEnemy*)GetPawn();
	BaseEnemy->StartSprint();
	FVector MyLoc = MyBot->GetActorLocation();

	float AddX = 0; ////// WhereShouldAIPatrolTo
	float AddY = 0;
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
	if (AddX && AddY)
	{
		float NewX = MyLoc[0] + AddX;
		float NewY = MyLoc[1] + AddY;
		MyLoc.Set(NewX, NewY, MyLoc[2]);
		BlackboardComp->SetValueAsVector(SetPatrolRoute, MyLoc);
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WhereShouldAIPatrolToFloat was an incorrect value"));
	}
	*/
}

void AAI_RangeController::AttackPlayer()
{
	//override
}
void AAI_RangeController::GoActive()
{
	//override
}



