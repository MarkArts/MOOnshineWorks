// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Projectile.h"
#include "AI_PegEnemyLight.h" 
#include "BlueprintLoader.h"

BlueprintLoader::BlueprintLoader()
{
	AddBP(FName("BP_Projectile"), TEXT("/Game/Blueprints/BP_Projectile"));
	AddBP(FName("AI_PegEnemyLight"), TEXT("/Game/Blueprints/AIBlueprints/ClosetEnemy/Services/AI_ClosetEnemy"));
	AddBP(FName("MyCharacter"), TEXT("/Game/Blueprints/MyCharacter"));
}

BlueprintLoader::~BlueprintLoader()
{

}

void BlueprintLoader::AddBP(FName Name, TCHAR* Path)
{
	ConstructorHelpers::FClassFinder<UObject> BP(Path);
	Classes.Add(Name, BP.Class);
}

TSubclassOf<class UObject> BlueprintLoader::GetBP(FName Name)
{
	TSubclassOf<class UObject> Result = (*Classes.Find(Name));

	if (Result){
		return Result;
	}
	else{
		return nullptr;
	}
}
