// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MOOnshineWorks, "MOOnshineWorks" );

FName GeneratePersistentId(AActor* Actor)
{
	UWorld* World =  Actor->GetWorld();
	if (World)
	{
		FVector Pos = Actor->GetActorLocation();
		FString PosString = FString::SanitizeFloat(round(Pos.X)) + FString::SanitizeFloat(round(Pos.Y)) + FString::SanitizeFloat(round(Pos.Z));
		
		FRotator Rot = Actor->GetActorRotation();
		FString RotString = FString::SanitizeFloat(round(Rot.Yaw)) + FString::SanitizeFloat(round(Rot.Roll)) + FString::SanitizeFloat(round(Rot.Pitch));

		FString Name = Actor->GetName();
		FString LevelName = Actor->GetLevel()->GetName();

		FString ID = Name + LevelName + PosString + RotString;

		return FName(*ID);
	}

	return FName();
}