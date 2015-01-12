// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Item.h"


AItem::AItem(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AItem::OnUse_Implementation()
{

}

void AItem::Use()
{
	OnUse();
}