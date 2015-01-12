// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "SlowDownDebuff.h"


ASlowDownDebuff::ASlowDownDebuff(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	name = "Slowdown";
}

void ASlowDownDebuff::SetDebuff(AActor* Target){
	if (IsValid(name)) {
		AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
		CharTarget->CharacterMovement->MaxWalkSpeed *= 6;
		SetTime(2.f, Target);
	}
}

void ASlowDownDebuff::QuitDebuff(){
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->CharacterMovement->MaxWalkSpeed /= 6;
	DebuffsActive.Remove(name);
}
