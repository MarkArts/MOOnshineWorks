// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "Helpers.h"
#include "MOOnshineWorksGameMode.h"
#include "BasicAnimationInstance.h"
#include "AI_RunnerEnemy.h"

AAI_BasicEnemy::AAI_BasicEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PawnSensor = PCIP.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor"));
	PawnSensor->SensingInterval = .25f; // 4 times per second
	PawnSensor->bOnlySensePlayers = true;
	PawnSensor->SetPeripheralVisionAngle(85.f);
	GetMesh()->SetCollisionProfileName(FName("EnemyCharacterMeshCollisionProfile"));
	GetMesh()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyPawnCollisionProfile"));
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Health = 0.f;
	Defense = 0.f;
	WalkSpeed = 0.f;
	Damage = 0.f;
	//EnemyDistanceShouldAttack = 0.f;
	ChargeSpeed = 0.f;
	AIPatrol = true;
	CanBeHit = true;
}

void AAI_BasicEnemy::PostInitializeComponents()
{
	PawnSensor->OnSeePawn.AddDynamic(this, &AAI_BasicEnemy::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AAI_BasicEnemy::OnHearNoise);
	Super::PostInitializeComponents();
}

void AAI_BasicEnemy::ReceiveBeginPlay()
{
	PersistentId = UHelpers::GeneratePersistentId( (AActor*) this );

	FActorSave* SaveState = UHelpers::GetSaveManager(GetWorld())->GetActorSave(PersistentId);
	if (SaveState)
	{
		if (SaveState->StopSpawn)
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
	GetCharacterMovement()->MaxWalkSpeed = 500;
}
void AAI_BasicEnemy::StartWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = 100;
}

void AAI_BasicEnemy::ChangeLightDark(bool CurrentDarkLight)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch Stance nu!"));
}

void AAI_BasicEnemy::DealDamage(float DamageInflicted)
{
	if (CanBeHit == true)
	{ 
		//Enemy wordt aangevallen en moet de speler gaan aanvallen!
		AAI_BasicController* controller = (AAI_BasicController*)GetController();
		controller->AISetAttackState();

		float FinalDamage = DamageInflicted - Defense;
		if (DamageInflicted >= 1.f && FinalDamage < 1)
		{
			FinalDamage = 1.f;
		}
		if (FinalDamage > 0)
		{
			Health -= FinalDamage;
            OnDealDamage();
		}
		if (Health <= 0)
		{
			Die();
		}
	}
}

void AAI_BasicEnemy::OnDealDamage_Implementation(){
    
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

	UHelpers::GetSaveManager(GetWorld())->AddActorSave(
		{
			GetPersistentId(),
			true,
			GetTransform().GetLocation(),
			GetTransform().Rotator()
		}
	);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Added Enemy to death enemies");

	//Indien de AI naar een AI_RunnerEnemy gecast kan worden dan items droppen!
	AAI_RunnerEnemy* AiChar = Cast<AAI_RunnerEnemy>(this);
	if (AiChar != NULL) //Het is een AI_RunnerEnemy
	{
		UWorld* const World = GetWorld();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "RunnerEnemy gedood nu items droppen!!");
		FVector SpawnLocation = AiChar->GetActorLocation();
		FRotator SpawnRotation = AiChar->GetActorRotation();

		ACollectible* NewObject = GetWorld()->SpawnActor<ACollectible>(AiChar->DropItem, SpawnLocation, SpawnRotation);
	}
	Destroy();

	OnDie();
}

void AAI_BasicEnemy::OnDie_Implementation()
{

}

FName AAI_BasicEnemy::GetPersistentId(){
	return PersistentId;
}

void AAI_BasicEnemy::AddImpulseToEnemy(FVector Impulse)
{
	//Falling State
	FVector Location = GetActorLocation();
	Location.Z += 10;
	SetActorLocation(Location);

	//physics van CapsuleComponent tijdelijk aanzetten!
	GetCapsuleComponent()->SetSimulatePhysics(true);

	//Omhoog gooien
	GetCharacterMovement()->Velocity = Impulse;

	//Geef impulse aan character!
	//CapsuleComponent->AddImpulse(Impulse, NAME_None, true);

	GetCapsuleComponent()->SetSimulatePhysics(false);
}
