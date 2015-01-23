// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Collectible.h"

ACollectible::ACollectible(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
//	ShouldSave = false;
//	UsedText = FString(TEXT(""));
}

void ACollectible::Save(bool StopSpawn)
{
	UHelpers::GetSaveManager(GetWorld())->AddActorSave(UHelpers::CreateActorSave(this, bHidden));
}

void ACollectible::OnCollect_Implementation(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Collectable object has no implementation");
}

void ACollectible::Collect(AActor* Target)
{
	OnCollect(Target);

	if (UsedText != TEXT(""))
	{
		UHelpers::DisplayText(GetWorld(), UsedText, 3.f);
	}

	if (ShouldSave){
		Save(true);
	}


	OnCollectDelegate.Broadcast(this);

	Destroy();
}

void ACollectible::ReceiveBeginPlay()
{
	if (ShouldSave){
		FActorSave* Save = UHelpers::GetSaveManager(GetWorld())->GetActorSave(UHelpers::GeneratePersistentId(this));
		if (Save)
		{
			UHelpers::ApplyActorSave(*Save, this);
		}
	}
	Super::ReceiveBeginPlay();
} 

void ACollectible::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ShouldSave){
		if (EEndPlayReason::RemovedFromWorld)
		{
			Save(false);
		}
	}
	Super::EndPlay(EndPlayReason);
}