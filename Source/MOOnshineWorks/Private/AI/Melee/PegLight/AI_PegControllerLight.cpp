// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "AI_PegControllerLight.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"
#include "AI_PegEnemyLight.h"
#include "AI_BasicController.h"
#include "BasicAnimationInstance.h"
#include "AI_BasicEnemy.h"

AAI_PegControllerLight::AAI_PegControllerLight(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		static ConstructorHelpers::FClassFinder<AAI_PegEnemyLight> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegLightMelee"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}
}

void AAI_PegControllerLight::AttackPlayer()
{
	Super::AttackPlayer();
}
void AAI_PegControllerLight::Patrol()
{
	Super::Patrol();
}
void AAI_PegControllerLight::GoActive()
{
	UBehaviorTree * BehaviorTree = NULL;
	AAI_PegEnemyLight* AiSpecific = Cast<AAI_PegEnemyLight>(GetPawn());
	FVector SpawnLocation = AiSpecific->GetActorLocation();
	FRotator SpawnRotation = AiSpecific->GetActorRotation();
	AAI_BasicEnemy* AiChar = Cast<AAI_BasicEnemy>(GetPawn());
	UWorld* const World = GetWorld();
	float FloatEnemyDistanceShouldAttack = AiChar->EnemyDistanceShouldAttack;
	bool ShouldAIPatrol = AiChar->AIPatrol;

	//Oude enemy destroyen
	AiSpecific->Destroy();

	//Nieuwe BlueprintEnemy Spawnen!
	AAI_BasicEnemy* NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(EnemyClass, SpawnLocation, SpawnRotation);

	if (NewPawn != NULL)
	{
		if (NewPawn->Controller == NULL)
		{
			NewPawn->SpawnDefaultController();
		}
		if (BehaviorTree != NULL)
		{
			AAIController* AIController = Cast<AAIController>(NewPawn->Controller);
			if (AIController != NULL)
			{
				AIController->RunBehaviorTree(BehaviorTree);
			}
		}
	}
	if (World)
	{
		World->SpawnActor<AActor>(AiChar->DeathBlueprint, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());
	}

	//De AIPatrol zetten
	NewPawn->AIPatrol = ShouldAIPatrol;
	//De EnemyDistanceShouldAttack setten
	NewPawn->EnemyDistanceShouldAttack = FloatEnemyDistanceShouldAttack;

	//Laat AI speler direct aanvallen!
	AAI_BasicController* Controller = (AAI_BasicController*)NewPawn->GetController();
	Controller->FoundPlayer();
	Controller->AISetAttackState();
}


