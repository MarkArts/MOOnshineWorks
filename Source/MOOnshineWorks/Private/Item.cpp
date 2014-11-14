// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Item.h"


AItem::AItem(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AItem::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("activate"));
}