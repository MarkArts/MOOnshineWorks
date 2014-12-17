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

	// the player hasn't probarly started yet at this point so we try to set all needed variables this way;
	AMOOnshineWorksCharacter* Character = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//Character->BeginPlay();

	ASaveManager* SaveManager = UHelpers::GetSaveManager(GetWorld());
	if (SaveManager->GetData()->Checkpoint.StreamingLevels.Num() <= 0)
	{
		// no chekpoint so first time playing
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorTransform(GetWorld()->GetAuthGameMode()->PlayerStarts[0]->GetTransform());
		UHelpers::CreateCheckpoint(Character);
	}
	else{
		((AMOOnshineWorksGameMode*)GetWorld()->GetAuthGameMode())->RestoreCheckpoint();
	}
}