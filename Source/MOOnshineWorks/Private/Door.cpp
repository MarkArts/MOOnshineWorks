// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnShineWorksCharacter.h"
#include "Door.h"

ADoor::ADoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DoorClosed = false;
}

void ADoor::DoorOpen_Implementation() {
	if (DoorClosed) {
		DoorClosed = false;

	}
	else {
		DoorClosed = true;
	}
	DoorOpen();
}