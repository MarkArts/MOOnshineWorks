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
	EnemyClass = TSubclassOf<AAI_BarrelEnemy>( *(BlueprintLoader::Get().GetBP(FName("AI_BarrelEnemy")) ) );
}

void ASpawnEnemy::SpawnRandomEnemy()
{
	TArray<FString> Parsed;
	TArray<FString> HowMuch;
	TArray<FString> TypeEnemy;
	const TCHAR* Delims[] = { TEXT(":"), TEXT(";") };

	float RandomNumber = (float)rand() / (float)RAND_MAX;
	int SetNumber = 0 + RandomNumber * (Enemies.Num());

	Enemies[SetNumber].ParseIntoArray(&Parsed, Delims, 2);

	int SizeOfArrayParsed = Parsed.Num() - 1;

	for (int x = 0; x <= SizeOfArrayParsed; x = x + 2) {
		HowMuch.Add(Parsed[x]);
	}
	for (int x = 1; x <= SizeOfArrayParsed; x = x + 2) {
		TypeEnemy.Add(Parsed[x]);
	}

	for (auto Itr(HowMuch.CreateIterator()); Itr; Itr++) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(HowMuch[Itr.GetIndex()]));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(TypeEnemy[Itr.GetIndex()]));
	}


	APawn* NewPawn = NULL;
	FVector BoxOnWorld = GetActorLocation();
	FRotator RotatorBoxOnWorld = GetActorRotation();

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

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(BoxOnWorld[2]));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Spawned"));
}

