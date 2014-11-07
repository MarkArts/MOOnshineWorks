// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_GhostController.h"
#include "MOOnshineWorksCharacter.h"

AAI_GhostController::AAI_GhostController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
}
void AAI_GhostController::Possess(class APawn *InPawn)
{
	Super::Possess(InPawn);
	AAI_Ghost* ghost = Cast<AAI_Ghost>(InPawn);
	if (ghost && ghost->Behavior)
	{
		BlackboardComp->InitializeBlackboard(ghost->Behavior->BlackboardAsset);
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		EnemyDistance = BlackboardComp->GetKeyID("EnemyDistance");

		BehaviorComp->StartTree(ghost->Behavior);
	}
}
void AAI_GhostController::SearchForEnemy()
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
void AAI_GhostController::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
}
void AAI_GhostController::AttackPlayer()
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AMOOnshineWorksCharacter* playerCharacter = Cast<AMOOnshineWorksCharacter>(*It);
		if (playerCharacter)
		{
			playerCharacter->CurrentHealth = playerCharacter->CurrentHealth - 1;
			
			if (playerCharacter->CurrentHealth == 0)
			{
				playerCharacter->Destroy();
			}
		}

	}
}

void AAI_GhostController::Patrol()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}
	
	const FVector MyLoc = MyBot->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(MyLoc[0]));

}
