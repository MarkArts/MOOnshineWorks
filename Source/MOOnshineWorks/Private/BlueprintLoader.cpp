// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Projectile.h"
#include "AI_BarrelEnemy.h"
#include "BlueprintLoader.h"

BlueprintLoader::BlueprintLoader()
{
    AddBP(FName("BP_Projectile"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Projectile"));
    AddBP(FName("AI_BarrelEnemy"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/BarrelEnemy/Services/AI_BarrelEnemy"));
	AddBP(FName("MyCharacter"), ANSI_TO_TCHAR("/Game/Blueprints/MyCharacter"));
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