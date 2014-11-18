// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Projectile.h"
#include "AI_ClosetEnemyLight.h" 
#include "BlueprintLoader.h"

BlueprintLoader::BlueprintLoader()
{

	/*
	#include "MOOnshineWorksGameMode.h"
	#include "BlueprintLoader.h"
	protected:
	virtual void ReceiveBeginPlay() override;
	//add these lines to header file
	*/

	/*
	AMOOnshineWorksGameMode* GameMode = Cast<AMOOnshineWorksGameMode>(GetWorld()->GetAuthGameMode());
	BlueprintClass = GameMode->BlueprintContainer-><FieldName>;
	//add these lines to the c++ file and replace <FieldName> with the field you want
	*/

	/*
	static ConstructorHelpers::FClassFinder<AProjectile> BP_Projectile(TEXT("/Game/Blueprints/BP_Projectile"));
	ProjectileClass = BP_Projectile.Class;

	static ConstructorHelpers::FClassFinder<AAI_ClosetEnemyLight> BP_AI_ClosetEnemyLight(TEXT("/Game/Blueprints/AIBlueprints/BarrelEnemy/Services/AI_BarrelEnemy"));
	AI_ClosetEnemyLight = BP_AI_ClosetEnemyLight.Class;

	static ConstructorHelpers::FClassFinder<APawn> BP_MOOnshineWorksCharacter(TEXT("/Game/Blueprints/MyCharacter"));
	MOOnshineWorksCharacter = BP_MOOnshineWorksCharacter.Class;
	*/
}

BlueprintLoader::~BlueprintLoader()
{

}
