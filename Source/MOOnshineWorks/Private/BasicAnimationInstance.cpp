// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "BasicAnimationInstance.h"

UBasicAnimationInstance::UBasicAnimationInstance(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIIdle = true;
	AIPatrolling = false;
	AIAttacking = false;
}


