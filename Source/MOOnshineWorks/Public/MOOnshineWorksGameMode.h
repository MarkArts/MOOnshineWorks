// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "BlueprintLoader.h"
#include "GameFramework/GameMode.h"
#include "TextDisplay.h"
#include "SaveManager.h"
#include "MOOnshineWorksGameMode.generated.h"

UCLASS(minimalapi)
class AMOOnshineWorksGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	//ASocket* Socket;

	ATextDisplay* DisplayHUD;
	ASaveManager* SaveManager;
};



