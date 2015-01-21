// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
//#include "AI_BasicController.h"
//#include "AI_BasicEnemy.h"
//#include "AI_PegEnemyDark.h"
//#include "AI_PegEnemyLight.h"
//#include "AI_PegControllerDark.h"
//#include "AI_BookEnemyLight.h"
//#include "AI_BookControllerLight.h"
#include "SpawnEnemy.h"

ASpawnEnemy::ASpawnEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/*
	Time = 4.f;
	Enemies.Add("1:PegEnemyLight;1:RangeBookEnemy");
	Repeat = false;
	ShouldSpawnEnemies = false;

	//Melee
	static ConstructorHelpers::FClassFinder<AAI_PegEnemyLight> PegLightBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegLightMelee"));
	if (PegLightBPClass.Class != NULL)
	{
		PegLightEnemyClass = PegLightBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AAI_PegEnemyDark> PegDarkBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_PegEnemyDark"));
	if (PegDarkBPClass.Class != NULL)
	{
		PegDarkEnemyClass = PegDarkBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AAI_GarbageEnemy> GarbageBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIGarbage"));
	if (GarbageBPClass.Class != NULL)
	{
		GarbageEnemyClass = GarbageBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AAI_BookEnemy> MeleeBookBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIBookMelee"));
	if (MeleeBookBPClass.Class != NULL)
	{
		MeleeBookEnemyClass = MeleeBookBPClass.Class;
	}

	//Range
	static ConstructorHelpers::FClassFinder<AAI_BookEnemyLight> BookBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIBook"));
	if (BookBPClass.Class != NULL)
	{
		RangeBookEnemyClass = BookBPClass.Class;
	}

	//Charge
	static ConstructorHelpers::FClassFinder<AAI_PianoEnemy> PianoBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIPiano"));
	if (PianoBPClass.Class != NULL)
	{
		PianoEnemyClass = PianoBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AAI_BarrelEnemy> BarrelBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AI_BarrelEnemy"));
	if (BarrelBPClass.Class != NULL)
	{
		BarrelEnemyClass = BarrelBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AAI_FridgeEnemy> FridgeBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/AIFridge"));
	if (FridgeBPClass.Class != NULL)
	{
		FridgeEnemyClass = FridgeBPClass.Class;
	}
	*/
}
/*
void ASpawnEnemy::SetTime(float Time)
{
	if (Repeat) {
		GetWorld()->GetTimerManager().SetTimer(this, &ASpawnEnemy::SpawnRandomEnemy, Time, true);
	}
}

void ASpawnEnemy::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	SetTime(Time);
	SpawnRandomEnemy();
	
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
		FBox BoxInfo = GetComponentsBoundingBox();
		FVector BoxSize = BoxInfo.GetSize();

		if (TypeEnemy[Itr.GetIndex()] == "PegEnemyLight") 
		{
			EnemyClass = PegLightEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "PegDarkEnemy") {
			EnemyClass = PegDarkEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "GarbageEnemy") {
			EnemyClass = GarbageEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "MeleeBookEnemy") {
			EnemyClass = MeleeBookEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "RangeBookEnemy") {
			EnemyClass = RangeBookEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "PianoChargeEnemy") {
			EnemyClass = PianoEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "BarrelChargeEnemy") {
			EnemyClass = BarrelEnemyClass;
		}
		else if (TypeEnemy[Itr.GetIndex()] == "FridgeChargeEnemy") {
			EnemyClass = FridgeEnemyClass;
		}

		if (GetWorld())
		{
			int32 MyShinyNewInt = FCString::Atoi(*HowMuch[Itr.GetIndex()]);
			for (int x = 1; x <= MyShinyNewInt; x++) {

				float random = (float)rand() / (float)RAND_MAX;
				float randomy = (float)rand() / (float)RAND_MAX;

				int xValue = 1 + random * ((3) - (1));
				int yValue = 1 + randomy * ((3) - (1));

				float z, y;

				if (xValue == 1)
					z = random * (0 + (BoxSize[0] / 2));
				else
					z = random * (0 - (BoxSize[0] / 2));
				if (yValue == 1)
					y = random * (0 + (BoxSize[1] / 2));
				else
					y = random * (0 - (BoxSize[1] / 2));

				BoxOnWorld[0] += z;
				BoxOnWorld[1] += y;

				if (ShouldSpawnEnemies)
				{
					if (BoxInfo.IsInside(BoxOnWorld))
					{
						NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(EnemyClass, BoxOnWorld, RotatorBoxOnWorld);
						FVector BoxOnWorld = GetActorLocation();
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
		}
	}
	EnemyClass = NULL;
	APawn* NewPawn = NULL;
}*/

