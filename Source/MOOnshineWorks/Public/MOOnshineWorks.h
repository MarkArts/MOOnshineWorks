// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __MOONSHINEWORKS_H__
#define __MOONSHINEWORKS_H__

#include "Engine.h"
#include "SaveManager.h"

#endif

UFUNCTION()
FName GeneratePersistentId(AActor* Actor);
UFUNCTION()
ASaveManager* GetSaveManager(UWorld* World);