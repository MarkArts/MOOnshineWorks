// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksGameMode.h"
#include "BaseLevelScriptActor.h"


ABaseLevelScriptActor::ABaseLevelScriptActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void ABaseLevelScriptActor::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	
	/*
	ULevelStreaming* FirstLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), FirstLevelName);
	//NewLevel = CreateLevelInstance(NewLevel, UniqueName);

	if (FirstLevel){
		FirstLevel->bShouldBeLoaded = true;
		FirstLevel->bShouldBeVisible = true;
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The name of the first level was wrong or wasn't set at all"));
	} */

	/* TODO: Find apropriate place for this call*/
	((AMOOnshineWorksGameMode*)GetWorld()->GetAuthGameMode())->RestoreCheckpoint();

//	Super::ReceiveBeginPlay();
}


