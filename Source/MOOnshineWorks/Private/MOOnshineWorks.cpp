// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MOOnshineWorks.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MOOnshineWorks, "MOOnshineWorks" );

FName GeneratePersistentId(AActor* Actor)
{
	UWorld* World =  Actor->GetWorld();
	if (World)
	{
		FVector Pos = Actor->GetActorLocation();
		FString PosString = FString::SanitizeFloat(abs(Pos.X)) + FString::SanitizeFloat(abs(Pos.Y)) + FString::SanitizeFloat(abs(Pos.Z));
		
		FRotator Rot = Actor->GetActorRotation();
		FString RotString = FString::SanitizeFloat(abs(Rot.Yaw)) + FString::SanitizeFloat(abs(Rot.Roll)) + FString::SanitizeFloat(abs(Rot.Pitch));

		FString Name = Actor->GetName();
		FString LevelName = Actor->GetLevel()->GetName();

		FString ID = Name + LevelName + PosString + RotString;

		return FName(*ID);
	}

	return FName();
}