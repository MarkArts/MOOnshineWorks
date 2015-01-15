// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "SlowDownDebuff.h"


ASlowDownDebuff::ASlowDownDebuff(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	name = "Slowdown";
	time = 5.f;
}

void ASlowDownDebuff::SetDebuff(AActor* Target){
	if (IsValid(this)) {
		DebuffsActive.Add(this);
		AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
		CharTarget->CharacterMovement->MaxWalkSpeed *= 6;
		SetTime(2.f);
	}
}

void ASlowDownDebuff::QuitDebuff(){
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->CharacterMovement->MaxWalkSpeed /= 6;
	DebuffsActive.Remove(this);
}

/*void ADebuffManager::SetTime(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(this, &ADebuffManager::QuitDebuff, Time, false);
}*/
