// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Collectible.h"


ACollectible::ACollectible(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ACollectible::OnCollect_Implementation(AActor* Target)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Collectable object has no implementation");
}