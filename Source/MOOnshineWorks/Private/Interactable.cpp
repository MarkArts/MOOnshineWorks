// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Interactable.h"

AInteractable::AInteractable(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	IsUsed = false;
	ShouldUseOnce = false;

	LastInteract = 0;
	Cooldown = 0;

//	DisplayText = FString(TEXT(""));
//	UsedText = FString(TEXT(""));
}

void AInteractable::OnInteract_Implementation(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Interacted with a object that had no implementation");
}

void AInteractable::Interact(AActor* Target)
{
	FDateTime CurrentTime = FDateTime::Now();
	if (Cooldown <= 0 || Cooldown <= CurrentTime.ToUnixTimestamp() - LastInteract)
	{
		if (ShouldUseOnce)
		{
			if (!IsUsed){
				IsUsed = true;
				UHelpers::GetSaveManager(GetWorld())->GetData()->Interactables.Add({
					UHelpers::GeneratePersistentId(this),
					true,
					StopSpawnWhenUsed
				});
				if (UsedText != TEXT(""))
				{
					UHelpers::DisplayText(GetWorld(), UsedText, 3.f);
				}
				OnInteract(Target);
				OnInteractDelegate.Broadcast(this);
				LastInteract = CurrentTime.ToUnixTimestamp();
			}
		}
		else{
			if (UsedText != TEXT(""))
			{
				UHelpers::DisplayText(GetWorld(), UsedText, 3.f);
			}
			OnInteract(Target);
			OnInteractDelegate.Broadcast(this);
			LastInteract = CurrentTime.ToUnixTimestamp();
		}
	}
}
void AInteractable::OnInRange_Implementation(AActor* Target)
{

}

void AInteractable::InRange(AActor* Target)
{
	OnInRange(Target);

	if (ShouldUseOnce)
	{
		if (!IsUsed)
		{
			if (DisplayText != TEXT(""))
			{
				UHelpers::DisplayText(GetWorld(), DisplayText);
			}
		}
	}
	else{
		if (DisplayText != TEXT(""))
		{
			UHelpers::DisplayText(GetWorld(), DisplayText);
		}
	}
}

void AInteractable::ReceiveBeginPlay()
{
	FInteractableSave* Save = UHelpers::GetSaveManager(GetWorld())->GetInteractableSave(UHelpers::GeneratePersistentId(this));

	if (ShouldUseOnce){
		if (Save)
		{
			if (Save->IsUsed)
			{
				IsUsed = true;
			}
		}
	}
	Super::ReceiveBeginPlay();

	if (StopSpawnWhenUsed)
	{
		if (Save)
		{
			if (Save->StopSpawn)
			{
				Destroy();
			}
		}
	}
}