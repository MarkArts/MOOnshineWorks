// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Interactable.h"


AInteractable::AInteractable(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Active = true;
}

void AInteractable::OnInteract_Implementation(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Interacted with a object that had no implementation");
}

void AInteractable::Interact(AActor* Target)
{
	OnInteract(Target);
}