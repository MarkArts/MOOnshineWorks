// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "MOOnshineWorksCharacter.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BasicAnimationInstance.h"

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
		StateAI = BlackboardComp->GetKeyID("StateAI");
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		EnemyDistance = BlackboardComp->GetKeyID("EnemyDistance");
		SetPatrolRoute = BlackboardComp->GetKeyID("PatrolTo");
		WhereShouldAIPatrolTo = BlackboardComp->GetKeyID("WhereShouldAIPatrolTo");
		OriginalPosition = BlackboardComp->GetKeyID("OriginalPosition");
		GotEnemyAsTarget = BlackboardComp->GetKeyID("GotEnemyInSight/Hear");
		LastSeenPosition = BlackboardComp->GetKeyID("LastSeenPosition");
		ShouldTheAIPatrol = BlackboardComp->GetKeyID("ShouldTheAIPatrol");

		BehaviorComp->StartTree(BaseChar->Behavior);
	}

	SetOriginalPosition();
}

void AAI_BasicController::SetOriginalPosition()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}
	const FVector MyLoc = MyBot->GetActorLocation();
	BlackboardComp->SetValueAsVector(OriginalPosition, MyLoc);
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
		//BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, BestDistSq);
		SetEnemy(BestPawn);
	}
}
void AAI_BasicController::SetEnemy(class APawn *InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
}

void AAI_BasicController::ChangeAIDarkLight(bool DarkLight) //Deze functie verwijderd alle AI's van Dark naar Light of andersom
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Stamina is " + DarkLight));

	if (DarkLight == false) //als die false is dan moeten ze naar Light versie
	{
		//Alle Dark enemies ophalen en destroyen

		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("yolo" + ActorItr->GetName()));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("yolo" + ActorItr->GetActorLocation().ToString()));
		}

	}
	if (DarkLight == true) //als die true is dan moeten ze naar Dark versie
	{

	}
}

void AAI_BasicController::Tick(float DeltaSeconds)
{

}

void AAI_BasicController::FoundPlayer() //Bool in blackboard setten voor behaviour tree
{
	BlackboardComp->SetValueAsBool(GotEnemyAsTarget, true);
}
void AAI_BasicController::ResetSight()
{
	BlackboardComp->SetValueAsBool(GotEnemyAsTarget, false);
}
void AAI_BasicController::LostPlayer() //Bool in blackboard setten voor behaviour tree en reset patrol key
{
	BlackboardComp->SetValueAsBool(GotEnemyAsTarget, false);
	BlackboardComp->SetValueAsFloat(WhereShouldAIPatrolTo, 0);

	//Pak positie speler en set deze om daar nog heen te lopen!
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const FVector MyLoc = Player->GetActorLocation();

	BlackboardComp->SetValueAsVector(LastSeenPosition, MyLoc);
}

void AAI_BasicController::SetAttackAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = true;
	BasicAnimInstance->AIPatrolling = false;
	BasicAnimInstance->AIIdle = false;
	//BasicAnimInstance->Jumping = false;
}
void AAI_BasicController::SetIdleAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = false;
	BasicAnimInstance->AIPatrolling = false;
	BasicAnimInstance->AIIdle = true;
	//BasicAnimInstance->Jumping = false;
}

void AAI_BasicController::SetPatrollingAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = false;
	BasicAnimInstance->AIPatrolling = true;
	BasicAnimInstance->AIIdle = false;
	//BasicAnimInstance->Jumping = false;
}
void AAI_BasicController::SetJumpingAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = false;
	BasicAnimInstance->AIPatrolling = false;
	BasicAnimInstance->AIIdle = false;
	//BasicAnimInstance->Jumping = true;
}
void AAI_BasicController::SetSpeedAnimation(float speed)
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	//BasicAnimInstance->Speed = speed;
}
void AAI_BasicController::AISetPatrolState()
{
	int State = 0;
	BlackboardComp->SetValueAsInt(StateAI, State);
	BlackboardComp->SetValueAsBool(GotEnemyAsTarget, false);
}
void AAI_BasicController::AISetAttackState()
{
	int State = 1;
	BlackboardComp->SetValueAsInt(StateAI, State);
}
void AAI_BasicController::AISetSearchState()
{
	int State = 2;
	BlackboardComp->SetValueAsInt(StateAI, State);
}
void AAI_BasicController::ShouldAIPatrol()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	//APawn* MyBot = GetPawn();
	if (BasicEnemy->AIPatrol == false) //AI moet niet patrollen en State is niet al gezet naar 3
	{
		BlackboardComp->SetValueAsBool(ShouldTheAIPatrol, false);
	}
	if (BasicEnemy->AIPatrol == true)
	{
		BlackboardComp->SetValueAsBool(ShouldTheAIPatrol, true);
	}
}
void AAI_BasicController::ActivateEnemy()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	//APawn* MyBot = GetPawn();
	//AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;

	MeshComponent->SetMaterial(1, BasicEnemy->TheMaterial);
}



