// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "Door.h"

ADoor::ADoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DoorClosed = false;
}

void ADoor::DoorOpen_Implementation() {
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player != NULL) {
		if (DoorClosed) {
			switch (KeyName)
			{
			default:
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("No Key -> Opens Magic Door"));
				DoorOpen();
				DoorClosed = false;
				break;
			case 1:
				for (auto Itr(Player->KeyPack.CreateIterator()); Itr; Itr++) {
					if (Player->KeyPack[Itr.GetIndex()]->GetKeyName() == 1) {
						DoorOpen();
						Player->KeyPack.RemoveAt(Itr.GetIndex());
						KeyName = EDoorKey::Type::None;
						DoorClosed = false;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Key #1 Removed from Inventory -> Opens Magic Door"));
						break;
					}
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("You dont have a Key #1"));
				break;
			case 2:
				for (auto Itr(Player->KeyPack.CreateIterator()); Itr; Itr++) {
					if (Player->KeyPack[Itr.GetIndex()]->GetKeyName() == 2) {
						DoorOpen();
						Player->KeyPack.RemoveAt(Itr.GetIndex());
						KeyName = EDoorKey::Type::None;
						DoorClosed = false;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Key #2 Removed from Inventory -> Opens Magic Door"));
						break;
					}
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("You dont have a Key #2"));
				break;
			case 3:
				for (auto Itr(Player->KeyPack.CreateIterator()); Itr; Itr++) {
					if (Player->KeyPack[Itr.GetIndex()]->GetKeyName() == 3) {
						DoorOpen();
						Player->KeyPack.RemoveAt(Itr.GetIndex());
						KeyName = EDoorKey::Type::None;
						DoorClosed = false;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Key #3 Removed from Inventory -> Opens Magic Door"));
						break;
					}
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("You dont have a Key #3"));
				break;
			}
		}
		else {
			DoorOpen();
			DoorClosed = true;
		}
	}
}