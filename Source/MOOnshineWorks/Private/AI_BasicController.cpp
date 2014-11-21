// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "MOOnshineWorksCharacter.h"
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
		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");
		EnemyDistance = BlackboardComp->GetKeyID("EnemyDistance");
		SetPatrolRoute = BlackboardComp->GetKeyID("PatrolTo");
		WhereShouldAIPatrolTo = BlackboardComp->GetKeyID("WhereShouldAIPatrolTo");
		OriginalPosition = BlackboardComp->GetKeyID("OriginalPosition");
		GotEnemyAsTarget = BlackboardComp->GetKeyID("GotEnemyInSight/Hear");
		LastSeenPosition = BlackboardComp->GetKeyID("LastSeenPosition");
		RecentlyAttackedEnemy = BlackboardComp->GetKeyID("RecentlyAttackedEnemy");

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Stamina is " + DarkLight));

	if (DarkLight == false) //als die false is dan moeten ze naar Light versie
	{
		//Alle Dark enemies ophalen en destroyen

		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("yolo" + ActorItr->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("yolo" + ActorItr->GetActorLocation().ToString()));
		}
		
	}
	if (DarkLight == true) //als die true is dan moeten ze naar Dark versie
	{

	}
}

void AAI_BasicController::Tick(float DeltaSeconds)
{
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//Check batteryLevel van speler voor Dark/Light switch
	AAI_BasicEnemy* Parent = (AAI_BasicEnemy*)GetActorClass();
	if (Parent->LightType == EnemyLightType::Dark && Player->LightPercentage >= 0.5f) //Destroy Dark types enemies en spawn Light types enemies
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("BatteryLevel boven 50 nu ChangeAIDarkLight() aanroepen!!"));
	}
	else if (Parent->LightType == EnemyLightType::Light && Player->LightPercentage <= 0.5f) //Destroy Light types enemies en spawn Dark types enemies
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("BatteryLevel onder 50 nu ChangeAIDarkLight() aanroepen!!"));
	}
}

void AAI_BasicController::FoundPlayer() //Bool in blackboard setten voor behaviour tree
{
	BlackboardComp->SetValueAsBool(GotEnemyAsTarget, true);
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
	APawn* Inst = Controller->GetControlledPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = true;
	BasicAnimInstance->AIPatrolling = false;
	BasicAnimInstance->AIIdle = false;
}
void AAI_BasicController::SetIdleAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetControlledPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = false;
	BasicAnimInstance->AIPatrolling = false;
	BasicAnimInstance->AIIdle = true;
}

void AAI_BasicController::SetPatrollingAnimation()
{
	AAI_BasicEnemy* BasicEnemy = (AAI_BasicEnemy*)GetPawn();
	AAI_BasicController* Controller = (AAI_BasicController*)BasicEnemy->GetController();
	APawn* Inst = Controller->GetControlledPawn();
	USkeletalMeshComponent* MeshComponent = BasicEnemy->Mesh;
	UBasicAnimationInstance* BasicAnimInstance = (UBasicAnimationInstance*)MeshComponent->GetAnimInstance();

	BasicAnimInstance->AIAttacking = false;
	BasicAnimInstance->AIPatrolling = true;
	BasicAnimInstance->AIIdle = false;
}

void AAI_BasicController::RecentlyAttackedEnemyTrue()
{
	BlackboardComp->SetValueAsBool(RecentlyAttackedEnemy, true);
}
void AAI_BasicController::RecentlyAttackedEnemyFalse()
{
	BlackboardComp->SetValueAsBool(RecentlyAttackedEnemy, false);
}





