// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Collectible.h"

ACollectible::ACollectible(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
//	ShouldSave = false;
//	UsedText = FString(TEXT(""));
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
		UHelpers::GetSaveManager(GetWorld())->AddActorSave(
		{
			UHelpers::GeneratePersistentId(this),
			false,
			GetTransform().GetLocation(),
			GetTransform().Rotator()
		});
	}

	Destroy();
}

void ACollectible::ReceiveBeginPlay()
{
	if (ShouldSave){
		FActorSave* Save = UHelpers::GetSaveManager(GetWorld())->GetActorSave(UHelpers::GeneratePersistentId(this));
		if (Save)
		{
			if (Save->StopSpawn)
			{
				Destroy();
			}
		}
	}
	Super::ReceiveBeginPlay();
}