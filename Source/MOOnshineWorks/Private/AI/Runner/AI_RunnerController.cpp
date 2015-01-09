// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "AI_BasicController.h"
#include "AI_RunnerController.h"


AAI_RunnerController::AAI_RunnerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}
void AAI_RunnerController::RunAway()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Runner: Ren Weg!");
}
void AAI_RunnerController::GoActive()
{

}


