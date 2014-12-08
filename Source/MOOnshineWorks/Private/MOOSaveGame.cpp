// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOSaveGame.h"


UMOOSaveGame::UMOOSaveGame(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerName = TEXT("Gaydor MacSwagginBrah");
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}


