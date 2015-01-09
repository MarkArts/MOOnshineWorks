// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MainHUD.h"


AMainHUD::AMainHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AMainHUD::DrawHUD()
{
	Super::DrawHUD();

	int DisplayStringsCount = DisplayStrings.Num();

	for (int i = DisplayStringsCount - 1; i >= 0; i--)
	{
		FDisplayString* DisplayString = &DisplayStrings[i];

		FVector2D Position = FVector2D(DisplayString->Position.X, DisplayString->Position.Y + i * 20);
		DrawText(DisplayString->Text, Position, Font, DisplayString->Scale, DisplayString->Color);
	}
}

void AMainHUD::AddDisplayString(FDisplayString DisplayStringToAdd)
{

	int32 DisplayStringsCount = DisplayStrings.Num();

	for (int32 i = 0; i < DisplayStringsCount; i++)
	{
		if (DisplayStrings[i].Text == DisplayStringToAdd.Text)
		{
			return;
		}
	}
	
	DisplayStrings.Add(DisplayStringToAdd);
}

void AMainHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	int DisplayStringsCount = DisplayStrings.Num();
	FDateTime CurrentTime = FDateTime::Now();

	for (int i = DisplayStringsCount - 1; i >= 0; i--)
	{
		FDisplayString* DisplayString = &DisplayStrings[i];

		FVector2D Position = FVector2D(DisplayString->Position.X, DisplayString->Position.Y + i * 20);

		if (DisplayString->DisplayTime == 0)
		{
			DisplayStrings.RemoveAt(i, 1);
		}
		else if (DisplayString->StartTime == 0)
		{
			DisplayString->StartTime = CurrentTime.ToUnixTimestamp();
		}
		else if (DisplayString->DisplayTime <= CurrentTime.ToUnixTimestamp() - DisplayString->StartTime)
		{
			DisplayStrings.RemoveAt(i, 1);
		}
	}
}