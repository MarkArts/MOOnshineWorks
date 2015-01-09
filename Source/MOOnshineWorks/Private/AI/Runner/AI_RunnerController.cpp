// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_RunnerController.h"


AAI_RunnerController::AAI_RunnerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}
void AAI_RunnerController::RunAway()
{
	AMOOnshineWorksCharacter* playerCharacter = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AAI_BasicController* AIController = Cast<AAI_BasicController>(GetPawn()->Controller);

	//Pak de x,y van de speler 
	FVector PlayerLocation = playerCharacter->GetActorLocation();
	//Pak de x,y van de Enemy
	FVector AiSpecificLocation = AiChar->GetActorLocation();
	//Bereken het verschil van deze waardes -/+ de character om te berekenen welke kant hij op moet!
	FVector difference = AiSpecificLocation - PlayerLocation;
	FVector VectorResult = AiSpecificLocation + (difference*3);

	AIController->BlackboardComp->SetValueAsVector(SetPatrolRoute, VectorResult);
}
void AAI_RunnerController::GoActive()
{
	//override
}
void AAI_RunnerController::ReduceTimer() //haal een seconde van TimerActive af en is die 0 roep dan TimeIsUp aan
{
	//override
}
void AAI_RunnerController::TimeIsUp()
{
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	AiChar->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Too late, no loot for yu");

	//Hier nog wat items droppen!!!
}

