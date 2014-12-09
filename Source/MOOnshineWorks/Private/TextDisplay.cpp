// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "TextDisplay.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"


ATextDisplay::ATextDisplay(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;

}

void ATextDisplay::DrawHUD(FString Output)
{
	// Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	FVector2D GameOverSize;
	GetTextSize(Output, GameOverSize.X, GameOverSize.Y, HUDFont);
	DrawText(Output, FColor::White, 50, 50, HUDFont);
}

