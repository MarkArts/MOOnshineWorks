// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "BaseLevelScriptActor.h"


ABaseLevelScriptActor::ABaseLevelScriptActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void ABaseLevelScriptActor::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	((AMOOnshineWorksGameMode*)GetWorld()->GetAuthGameMode())->RestoreCheckpoint();
}