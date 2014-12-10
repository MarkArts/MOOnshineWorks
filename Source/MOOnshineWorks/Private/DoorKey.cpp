// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "DoorKey.h"


ADoorKey::ADoorKey(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void ADoorKey::SetKeyName(EDoorKey::Type InsertKey) {
	KeyName = InsertKey;
}

FString ADoorKey::OnPickedUp() {
	switch (KeyName) {
	case 0:
		return "Deze sleutel heeft geen door.";
		break;
	case 1:
		return "Rode sleutel opgepakt.";
		break;
	case 2:
		return "Groene sleutel opgepakt.";
		break;
	case 3:
		return "Blauwe sleutel opgepakt.";
		break;
	default:
		return "Deze sleutel heeft geen door.";
		break;
	}
}

int8 ADoorKey::GetKeyName() {
	return KeyName;
}

void ADoorKey::Collect(AActor* Target)
{
	OnCollect(Target);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "KEY");
	AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
	CharTarget->AddKeyToKeyPack(this);
	Destroy();
}

