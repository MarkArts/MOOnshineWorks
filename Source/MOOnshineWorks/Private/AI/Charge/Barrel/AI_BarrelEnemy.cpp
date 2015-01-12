// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BarrelEnemy.h"
#include "AI_BarrelController.h"


AAI_BarrelEnemy::AAI_BarrelEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
    AIControllerClass = AAI_BarrelController::StaticClass();
    
	PianoPushPower = 0;

	ChargeAudio = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("In-World Audio Pickup Sound"));
}


