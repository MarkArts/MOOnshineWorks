// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_BasicEnemy.h"
#include "AI_BarrelEnemy.h"
#include "AI_BarrelController.h"
#include "AI_BookEnemyLight.h"
#include "AI_BookControllerLight.h"
#include "SpawnEnemy.h"

ASpawnEnemy::ASpawnEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	Time = 4.f;
	Enemies.Add("2:BarrelEnemy;2:BookEnemy");
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
}

void ASpawnEnemy::SpawnRandomEnemy()
{
	TArray<FString> Parsed;
	TArray<FString> HowMuch;
	TArray<FString> TypeEnemy;
	const TCHAR* Delims[] = { TEXT(":"), TEXT(";") };

	float RandomNumber = (float)rand() / (float)RAND_MAX;
	int SetNumber = RandomNumber * (Enemies.Num());

	Enemies[SetNumber].ParseIntoArray(&Parsed, Delims, 2);

	int SizeOfArrayParsed = Parsed.Num() - 1;

	for (int x = 0; x <= SizeOfArrayParsed; x = x + 2) {
		HowMuch.Add(Parsed[x]);
	}
	for (int x = 1; x <= SizeOfArrayParsed; x = x + 2) {
		TypeEnemy.Add(Parsed[x]);
	}

	for (auto Itr(HowMuch.CreateIterator()); Itr; Itr++) {
		APawn* NewPawn = NULL;
		FVector BoxOnWorld = GetActorLocation();
		FRotator RotatorBoxOnWorld = GetActorRotation();

		if (TypeEnemy[Itr.GetIndex()] == "BarrelEnemy") {
			EnemyClass = TSubclassOf<AAI_BarrelEnemy>(*(BlueprintLoader::Get().GetBP(FName("AI_BarrelEnemy"))));
		}
		else if (TypeEnemy[Itr.GetIndex()] == "BookEnemy") {
			EnemyClass = TSubclassOf<AAI_BarrelEnemy>(*(BlueprintLoader::Get().GetBP(FName("AI_BarrelEnemy"))));
		}

		if (GetWorld())
		{
			int32 MyShinyNewInt = FCString::Atoi(*HowMuch[Itr.GetIndex()]);
			for (int x = 1; x <= MyShinyNewInt; x++) {
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
		}
	}
	EnemyClass = NULL;
}

