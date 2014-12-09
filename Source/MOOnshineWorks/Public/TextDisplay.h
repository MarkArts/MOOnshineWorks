// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TextDisplay.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ATextDisplay : public AHUD
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	UFont* HUDFont;

	void DrawHUD(FString Output);
	
};
