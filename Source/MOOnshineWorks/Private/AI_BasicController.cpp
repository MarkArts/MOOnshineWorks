// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "MOOnshineWorksCharacter.h"


AAI_BasicController::AAI_BasicController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
}

void AAI_BasicController::Possess(class APawn *InPawn)
{
	Super::Possess(InPawn);
	AAI_BasicEnemy* BaseChar = Cast<AAI_BasicEnemy>(InPawn);
	if (BaseChar && BaseChar->Behavior)
	{
		BlackboardComp->InitializeBlackboard(BaseChar->Behavior->BlackboardAsset);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		EnemyDistance = BlackboardComp->GetKeyID("EnemyDistance");
		SetPatrolRoute = BlackboardComp->GetKeyID("PatrolTo");

		BehaviorComp->StartTree(BaseChar->Behavior);
	}
}

void AAI_BasicController::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AMOOnshineWorksCharacter* BestPawn = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AMOOnshineWorksCharacter* TestPawn = Cast<AMOOnshineWorksCharacter>(*It);
		if (TestPawn)
		{
			const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}

	if (BestPawn)
	{
		BlackboardComp->SetValueAsFloat(EnemyDistance, BestDistSq);
		SetEnemy(BestPawn);
	}
}
void AAI_BasicController::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
}

