// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Projectile.h"
#include "AI_PegEnemyLight.h"
//#include "BlueprintLoader.generated.h"
/**
 * 
 */
class MOONSHINEWORKS_API BlueprintLoader
{

private:

	//static BlueprintLoader* Instance;
	BlueprintLoader();
	~BlueprintLoader();
	BlueprintLoader(BlueprintLoader const&); // Don't Implement
	void operator=(BlueprintLoader const&); // Don't implement

	TMap<FName, TSubclassOf<class UObject>> Classes;

public:

	//void Initialize(const class FPostConstructInitializeProperties& PCIP);
	static BlueprintLoader& Get(){
		static BlueprintLoader	Instance;
		return Instance;
	};

	void AddBP(FName Name, TCHAR* Path);
	TSubclassOf<class UObject> GetBP(FName Name);

};
