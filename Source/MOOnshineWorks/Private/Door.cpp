// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Interactable.h"
#include "Door.h"

ADoor::ADoor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	DoorClosed = false;
}

void ADoor::DoorOpen_Implementation() {
	
}

void ADoor::OnInteract_Implementation(AActor* Target)
{
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player != NULL) {
		if (DoorClosed) {
			if (KeyName != 0) {
				if (Player->HasKeyHolder(KeyName)) {
					DoorOpen();
					KeyName = EDoorKey::Type::None;
					DoorClosed = false;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Key opens the door"));
				}
				else {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Door is Locked")));
				}
			}
			else {
				DoorOpen();
				DoorClosed = false;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Door just opens"));
			}
		}
		else {
			DoorOpen();
			DoorClosed = true;
		}
	}
}