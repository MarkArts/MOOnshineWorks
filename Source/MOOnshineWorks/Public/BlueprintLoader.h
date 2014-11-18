// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Projectile.h"
#include "AI_ClosetEnemyLight.h"
//#include "BlueprintLoader.generated.h"
/**
 * 
 */
class MOONSHINEWORKS_API BlueprintLoader

public:
	//TSubclassOf<class AProjectile> ProjectileClass;
	//TSubclassOf<class AAI_ClosetEnemyLight> AAI_ClosetEnemyLight;
	//TSubclassOf<class APawn> MOOnshineWorksCharacter;
=======
>>>>>>> origin/Develop

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
