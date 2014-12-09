// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksGameMode.h"
#include "Socket.h"
#include "BaseLevelScriptActor.h"
#include "MOOnshineWorksCharacter.h"

AMOOnshineWorksGameMode::AMOOnshineWorksGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	if (GetWorld()){

		BlueprintLoader::Get().AddBP(FName("AI_PegEnemyDark"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/PegAIDark/Blueprint/AI_PegEnemyDark"));
		//BlueprintLoader::Get().AddBP(FName("BP_Projectile"), ANSI_TO_TCHAR("/Game/Blueprints/BP_Projectile"));
		BlueprintLoader::Get().AddBP(FName("AI_BookEnemyLight"), ANSI_TO_TCHAR("/Game/Blueprints/AIBlueprints/BookAILight/AI_BookEnemyLight"));
		BlueprintLoader::Get().AddBP(FName("MyCharacter"), ANSI_TO_TCHAR("/Game/Blueprints/MyCharacter"));
		BlueprintLoader::Get().AddBP(FName("PistolClass"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Pistol/BP_Pistol"));
		BlueprintLoader::Get().AddBP(FName("ShotgunClass"), ANSI_TO_TCHAR("/Game/Blueprints/Guns/Shotgun/BP_Shotgun"));
		//BlueprintLoader::Get().AddBP(FName("ProjectileDeath"), ANSI_TO_TCHAR("/Game/Blueprints/BP_ProjectileDeath"));

		// set default pawn class to our Blueprinted character
		DefaultPawnClass = TSubclassOf<APawn>(*(BlueprintLoader::Get().GetBP(FName("MyCharacter"))));
		SaveManager = (ASaveManager*)GetWorld()->SpawnActor(ASaveManager::StaticClass());
		SaveManager->Load();
	}
}
