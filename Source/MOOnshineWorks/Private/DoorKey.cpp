// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnshineWorksCharacter.h"
#include "DoorKey.h"


ADoorKey::ADoorKey(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	
}

void ADoorKey::SetKeyName(EDoorKey::Type InsertKey) {
	KeyName = InsertKey;
}

EDoorKey::Type ADoorKey::GetKeyName() {
	return KeyName;
}

void ADoorKey::Collect(AActor* Target)
{
	AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
	CharTarget->AddKeyToKeyHolder(GetKeyName());
	Super::Collect(Target);
}

void ADoorKey::OnCollect_Implementation(AActor* Target)
{

}

