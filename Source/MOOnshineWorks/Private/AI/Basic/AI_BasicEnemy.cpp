// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicEnemy.h"
#include "AI_BasicController.h"
#include "Helpers.h"
#include "MOOnshineWorksGameMode.h"
#include "BasicAnimationInstance.h"
#include "AI_RunnerEnemy.h"
#include "MOOnshineWorksCharacter.h"
#include "GameFramework/Character.h"

AAI_BasicEnemy::AAI_BasicEnemy(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	//if (HasAnyFlags(RF_ClassDefaultObject) == false)
	//{
		static ConstructorHelpers::FClassFinder<AAI_BasicEnemy> DestructiblePegBPClass(TEXT("/Game/Blueprints/AIBlueprints/AllBlueprints/Destructible/PegEnemyLightDestructible"));
		if (DestructiblePegBPClass.Class != NULL)
		{
			DestructibleEnemyClass = DestructiblePegBPClass.Class;
		}
	//}

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
	AIPatrol = true;
	CanBeHit = true;
}

/* Mark: I moved this to recieve begin play as a test to see if declerate cleanup of enemie wil crash less*/
//void AAI_BasicEnemy::PostInitializeComponents()
//{
//	PawnSensor->OnSeePawn.AddDynamic(this, &AAI_BasicEnemy::OnSeePawn);
//	PawnSensor->OnHearNoise.AddDynamic(this, &AAI_BasicEnemy::OnHearNoise);
//	Super::PostInitializeComponents();
//}

void AAI_BasicEnemy::ReceiveBeginPlay()
{
	PersistentId = UHelpers::GeneratePersistentId( (AActor*) this );

	PawnSensor->OnSeePawn.AddDynamic(this, &AAI_BasicEnemy::OnSeePawn);
	PawnSensor->OnHearNoise.AddDynamic(this, &AAI_BasicEnemy::OnHearNoise);

	FActorSave SaveState = UHelpers::GetSaveManager(GetWorld())->GetActorSave(PersistentId);
	if (!SaveState.Id.IsNone())
	{
		UHelpers::ApplyActorSave(SaveState, this);
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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "YOU DAMN FUCKUP UP MATE. Couldn't find controller");
	}

	Save(true);

	//Indien de AI naar een AI_RunnerEnemy gecast kan worden dan items droppen!
	AAI_RunnerEnemy* AiChar = Cast<AAI_RunnerEnemy>(this);
	if (AiChar != NULL) //Het is een AI_RunnerEnemy
	{
		UWorld* const World = GetWorld();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "RunnerEnemy gedood nu items droppen!!");
		FVector SpawnLocation = AiChar->GetActorLocation();
		FRotator SpawnRotation = AiChar->GetActorRotation();

		ACollectible* NewObject = GetWorld()->SpawnActor<ACollectible>(AiChar->DropItem, SpawnLocation, SpawnRotation);
	}

	OnDie();
}

void AAI_BasicEnemy::OnDie_Implementation()
{
	AAI_BasicEnemy* NewPawn = NULL;
	FVector SpawnLocation = this->GetActorLocation();
	//SpawnLocation[2] = SpawnLocation[2] + 50;
	FRotator SpawnRotation = this->GetActorRotation();
	
	OnDeathDelegate.Broadcast(this);
	Destroy();

	//Spawn Destructible Mesh
	if (DestructibleEnemyClass != NULL)
	{ 
		NewPawn = GetWorld()->SpawnActor<AAI_BasicEnemy>(DestructibleEnemyClass, SpawnLocation, SpawnRotation);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "DestructibleEnemyClass is leeeeeg OMFG!!");
	}
}

void AAI_BasicEnemy::AIBecameActive()
{
	OnAIBecameActive();
}
void AAI_BasicEnemy::OnAIBecameActive_Implementation()
{
	//Event opgooien voor sound afspelen in Blueprints
}

FName AAI_BasicEnemy::GetPersistentId(){
	return PersistentId;
}

void AAI_BasicEnemy::Save(bool StopSpawn){
	UHelpers::GetSaveManager(GetWorld())->AddActorSave(UHelpers::CreateActorSave(this, StopSpawn, false, GetPersistentId()));
}

void AAI_BasicEnemy::AddImpulseToEnemy(FVector Impulse)
{
	//Falling State
	FVector Location = GetActorLocation();
	Location.Z += 30;
	SetActorLocation(Location);

	//physics van CapsuleComponent tijdelijk aanzetten!
	GetCapsuleComponent()->SetSimulatePhysics(true);

	Impulse.Z = Location.Z;

	//Omhoog gooien
	GetCharacterMovement()->Velocity = Impulse;

	//Geef impulse aan character!
	//CapsuleComponent->AddImpulse(Impulse, NAME_None, true);

	GetCapsuleComponent()->SetSimulatePhysics(false);
}
