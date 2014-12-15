// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Interactable.h"


AInteractable::AInteractable(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
<<<<<<< HEAD
	IsUsed = false;
	ShouldUseOnce = false;

	DisplayText = FString(TEXT(""));
	UsedText = FString(TEXT(""));
=======
	Active = true;
>>>>>>> origin/Design
}

void AInteractable::OnInteract_Implementation(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Interacted with a object that had no implementation");
}

void AInteractable::Interact(AActor* Target)
{
<<<<<<< HEAD
	if (ShouldUseOnce)
	{
		if (!IsUsed){
			IsUsed = true;
			UHelpers::GetSaveManager(GetWorld())->GetData()->Interactables.Add({
				UHelpers::GeneratePersistentId(this),
				true
			});
			// display UsedText;
			OnInteract(Target);
		}
	}
	else{
		// display UsedText;
		OnInteract(Target);
	}
}
void AInteractable::OnInRange_Implementation(AActor* Target)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Interacted with a object that had no implementation");
}

void AInteractable::InRange(AActor* Target)
{
	OnInRange(Target);
}

void AInteractable::ReceiveBeginPlay()
{
	if (ShouldUseOnce){
		FInteractableSave* Save = UHelpers::GetSaveManager(GetWorld())->GetInteractableSave(UHelpers::GeneratePersistentId(this));
		if (Save)
		{
			if (Save->IsUsed)
			{
				IsUsed = true;
			}
		}
	}
=======
	OnInteract(Target);
>>>>>>> origin/Design
}