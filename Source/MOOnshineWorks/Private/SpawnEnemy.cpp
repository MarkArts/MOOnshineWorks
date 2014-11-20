// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_BarrelEnemy.h"
#include "AI_BarrelController.h"
#include "SpawnEnemy.h"

ASpawnEnemy::ASpawnEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	/*if (EnemyClass == NULL){
		
		static ConstructorHelpers::FClassFinder<AAI_BarrelEnemy> PlayerPawnBPClass(TEXT("/Game/Blueprints/AIBlueprints/BarrelEnemy/Services/AI_BarrelEnemy"));

		if (PlayerPawnBPClass.Class != NULL)
		{
			EnemyClass = PlayerPawnBPClass.Class;
		}
	}*/
	Time = 4.f;
}

void ASpawnEnemy::SetTime(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(this, &ASpawnEnemy::SpawnRandomEnemy, Time, true);
}

void ASpawnEnemy::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	SetTime(Time);
	AMOOnshineWorksGameMode* GameMode = Cast<AMOOnshineWorksGameMode>(GetWorld()->GetAuthGameMode());
	EnemyClass = TSubclassOf<AAI_BarrelEnemy>( *(BlueprintLoader::Get().GetBP(FName("AI_BarrelEnemy")) ) );
}

void ASpawnEnemy::SpawnRandomEnemy()
{
	//UWorld* const World = GetWorld();
	APawn* NewPawn = NULL;
	FVector BoxOnWorld = GetActorLocation();
	FRotator RotatorBoxOnWorld = GetActorRotation();
//	if (World)
//	{
		//AAI_BarrelEnemy* enemy = GetWorld()->SpawnActor<AAI_BarrelEnemy>(EnemyClass, BoxOnWorld, RotatorBoxOnWorld);

	if (GetWorld())
	{
		NewPawn = GetWorld()->SpawnActor<APawn>(EnemyClass, BoxOnWorld, RotatorBoxOnWorld);
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
	}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(BoxOnWorld[2]));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Spawned"));
//	}
}

