// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "DebuffManager.h"


ADebuffManager::ADebuffManager(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	DebuffType = "Debuff Manager";
}

void ADebuffManager::SetDebuff(AActor* Target){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("SetDebuff(From DebuffManager);"));
}

void ADebuffManager::QuitDebuff(){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("QuitDebuff();"));
}

void ADebuffManager::StartDebuff(ADebuffManager* Target, AActor* Actor) {
	Target->SetDebuff(Actor);
}


void ADebuffManager::OnSetDebuff_Implementation(AActor* Target){

}

/*
void ADebuffManager::Start(ADebuffManager* Target) {
	SetDebuff(Target);
}
*/

bool ADebuffManager::IsValid(ADebuffManager* nameDebuff) {
	for (auto Itr(DebuffsActive.CreateIterator()); Itr; Itr++) {
		if (DebuffsActive[Itr.GetIndex()]->DebuffType == nameDebuff->DebuffType) {
			nameDebuff->SetTime(nameDebuff->DebuffTime);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ("Debuff is al geapplied, timer herstart!"));
			return false;
		}
	}
	FVector2D place;
	place.Set(-80.f, -80.f);
	UHelpers::DisplayText(GetWorld(), "You got: " + nameDebuff->DebuffType, 3.f, place);
	return true;
}

void ADebuffManager::SetTime(float Time)
{
	GetWorld()->GetTimerManager().SetTimer(this, &ADebuffManager::QuitDebuff, Time, false);
}
