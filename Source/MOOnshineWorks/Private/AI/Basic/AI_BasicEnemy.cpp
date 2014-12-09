// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "MOOnshineWorksGameMode.h"
#include "BasicAnimationInstance.h"

AAI_BasicEnemy::AAI_BasicEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PawnSensor = PCIP.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = .25f; // 4 times per second
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SetPeripheralVisionAngle(85.f);
	Mesh->SetCollisionProfileName(FName("EnemyCharacterMeshCollisionProfile"));
	CapsuleComponent->SetCollisionProfileName(FName("EnemyPawnCollisionProfile"));

	Health = 0.f;
	Defense = 0.f;
	Speed = 0.f;
	Damage = 0.f;
	AIPatrol = true;
}

void AAI_BasicEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensor->OnSeePawn.AddDynamic(this, &AAI_BasicEnemy::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AAI_BasicEnemy::OnHearNoise);
}

void AAI_BasicEnemy::ReceiveBeginPlay()
{
	PersistentId = GeneratePersistentId( (AActor*) this );

	FEnemySave* SaveState = nullptr;
	TArray<FEnemySave> Enemies = GetSaveManager(GetWorld())->GetData().Enemies;

	for (int32 b = 0; b < Enemies.Num(); b++)
	{
		if (Enemies[b].Id == PersistentId)
		{
			SaveState = &Enemies[b];
		}
	}

	if (SaveState)
	{
		if (SaveState->Death)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Enemy was already death");
			Destroy();
		}
	}
}

void AAI_BasicEnemy::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI hoort me!"));

	AAI_BasicController* cont = (AAI_BasicController*)GetController();
	cont->FoundPlayer();
}

void AAI_BasicEnemy::OnSeePawn(APawn *OtherPawn)
{	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI ziet me!"));

	AAI_BasicController* cont = (AAI_BasicController*)GetController();
	cont->FoundPlayer();
}

void AAI_BasicEnemy::StartSprint()
{
	CharacterMovement->MaxWalkSpeed = 500;
}
void AAI_BasicEnemy::StartWalk()
{
	CharacterMovement->MaxWalkSpeed = 100;
}

void AAI_BasicEnemy::ChangeLightDark(bool CurrentDarkLight)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch Stance nu!"));
}

void AAI_BasicEnemy::DealDamage(float DamageInflicted)
{
	float FinalDamage = Damage - Defense;
	if (FinalDamage > 0)
	{
		Health -= FinalDamage;
	}
	if (Health <= 0)
	{
		Die();
	}
}

void AAI_BasicEnemy::Die()
{
	//Physics/animation voor dood afspelen en daarna verwijderen!
	AAI_BasicController* TargetEnemyController = (AAI_BasicController*)GetController();
	if (TargetEnemyController){
		//TargetEnemyController->SetDeathAnimation();
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "YOU DAMN FUCKUP UP MATE. Couldn't find controller");
	}



	FSave SaveData = ((AMOOnshineWorksGameMode*)UGameplayStatics::GetGameMode(GetWorld()))->SaveManager->GetData();
	SaveData.Enemies.Add(
		{
			GetPersistentId(),
			true
		}
	);
	GetSaveManager(GetWorld())->SetData(SaveData);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Added Enemy to death enemies");

	Destroy();
}

FName AAI_BasicEnemy::GetPersistentId(){
	return PersistentId;
}
