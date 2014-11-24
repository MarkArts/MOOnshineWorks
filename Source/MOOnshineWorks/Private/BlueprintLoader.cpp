// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Projectile.h"
#include "AI_PegEnemyLight.h" 
#include "AI_BookEnemyLight.h"
#include "BlueprintLoader.h"

BlueprintLoader::BlueprintLoader()
{
	AddBP(FName("AI_PegEnemyLight"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/ClosetEnemy/Services/AI_ClosetEnemy"));
	AddBP(FName("BP_Projectile"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Projectile"));
	AddBP(FName("AI_BookEnemyLight"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/BookLight/AI_BookEnemyLight"));
	AddBP(FName("MyCharacter"), ANSI_TO_TCHAR("/Game/Blueprints/MyCharacter"));
	AddBP(FName("PistolClass"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Pistol"));
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
