// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Projectile.h"
//#include "AI_PegEnemyDark.h" 
//#include "AI_BookEnemyLight.h"
//#include "AI_BarrelEnemy.h"
#include "BlueprintLoader.h"

BlueprintLoader::BlueprintLoader()
{

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
