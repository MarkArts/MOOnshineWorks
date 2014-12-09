// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DoorKey.h"


ADoorKey::ADoorKey(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}


void ADoorKey::SetKeyName(EDoorKey::Type InsertKey) {
	KeyName = InsertKey;
}

int8 ADoorKey::GetKeyName() {
	return KeyName;
}

