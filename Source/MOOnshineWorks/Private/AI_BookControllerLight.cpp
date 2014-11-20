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
void AAI_BookControllerLight::BookPatrol()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	AAI_BasicEnemy* BaseEnemy = (AAI_BasicEnemy*)GetPawn();
	BaseEnemy->StartWalk();
	FVector MyLoc = MyBot->GetActorLocation();
	
	float AddX = 0;
	float AddY = 0;
	float NewWhereShouldAIPatrolTo = 0; //Voor de Blackboard key: WhereShouldAIPatrolTo

	//Check de huidige waarde van WhereShouldAIPatrolTo
	if (WhereShouldAIPatrolTo == 5)
	{
		AddX = 100;
		AddY = 100;
		NewWhereShouldAIPatrolTo = 6;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("kom ik hier! if1"));
	} 
	else if (WhereShouldAIPatrolTo == 6)
	{
		AddX = 100;
		AddY = -100;
		NewWhereShouldAIPatrolTo = 7;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("kom ik hier! if2"));
	}
	else if (WhereShouldAIPatrolTo == 7)
	{
		AddX = -100;
		AddY = -100;
		NewWhereShouldAIPatrolTo = 8;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("kom ik hier! if3"));
	}
	else if (WhereShouldAIPatrolTo == 8)
	{
		AddX = -100;
		AddY = 100;
		NewWhereShouldAIPatrolTo = 9;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("kom ik hier! if4"));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(NewWhereShouldAIPatrolTo));
	//Pas de WhereShouldAIPatrolTo nummer aan zodat die een andere kant op loopt volgende keer
	BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, NewWhereShouldAIPatrolTo);

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
