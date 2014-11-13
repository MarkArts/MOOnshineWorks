// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksGameMode.h"
#include "Socket.h"
#include "BaseLevelScriptActor.h"
#include "MOOnshineWorksCharacter.h"

AMOOnshineWorksGameMode::AMOOnshineWorksGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character

	if (GetWorld()){

		ABaseLevelScriptActor* level = (ABaseLevelScriptActor*)GetWorld()->GetLevelScriptActor();
		if (level){
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (*level).LevelName);

			static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
			if (PlayerPawnBPClass.Class != NULL)
			{
					DefaultPawnClass = PlayerPawnBPClass.Class;
			}

			Socket = (ASocket*)GetWorld()->SpawnActor(ASocket::StaticClass());
			Socket->start("MarksSocket", "127.0.0.1", 4243);

		}
	}
}
