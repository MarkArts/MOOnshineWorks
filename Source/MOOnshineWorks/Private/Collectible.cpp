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
	UHelpers::GetSaveManager(GetWorld())->AddActorSave(UHelpers::CreateActorSave(this, StopSpawn, (bHidden > 0) , Id));
}

void ACollectible::OnCollect_Implementation(AActor* Target)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Collectable object has no implementation");
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
	Id = UHelpers::GeneratePersistentId(this);

	if (ShouldSave){
		FActorSave Save = UHelpers::GetSaveManager(GetWorld())->GetActorSave(Id);
		if (!Save.Id.IsNone())
		{
			UHelpers::ApplyActorSave(Save, this);
		}
	}

	Super::ReceiveBeginPlay();
} 

void ACollectible::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}