// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MOOnShineWorksCharacter.h"
#include "Door.h"


ADoor::ADoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DoorClosed = true;
}

void ADoor::DoorOpen() {
	if (DoorClosed) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Open Door"));
		FRotator DoorRotator = this->GetActorRotation();
		FVector DoorLocation = this->GetActorLocation();
		DoorLocation[0] -= 90;
		DoorLocation[1] += 20;
		DoorRotator.Yaw += 90;
		this->SetActorLocation(DoorLocation);
		this->SetActorRotation(DoorRotator);
		DoorClosed = false;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Close Door"));
		FRotator DoorRotator = this->GetActorRotation();
		FVector DoorLocation = this->GetActorLocation();
		DoorLocation[0] += 90;
		DoorLocation[1] -= 20;
		DoorRotator.Yaw -= 90;
		this->SetActorLocation(DoorLocation);
		this->SetActorRotation(DoorRotator);
		DoorClosed = true;
	}
	
}