// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "BlueprintLoader.h"
#include "GameFramework/GameMode.h"
#include "Socket.h"
#include "MOOnshineWorksGameMode.generated.h"

UCLASS(minimalapi)
class AMOOnshineWorksGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
public:
	//UPROPERTY(VisibleAnywhere, Category = "Blueprints")
	BlueprintLoader* BlueprintContainer;

	ASocket* Socket;
};



