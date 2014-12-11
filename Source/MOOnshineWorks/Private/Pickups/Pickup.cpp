// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// The pickup is valid when it is created.
	bIsActive = true;

	// Create the root SphereComponent to handle the pickup's collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	BaseCollisionComponent->SetCollisionProfileName("PickupCollision");
	// Set the SphereComponent as the root component.
	RootComponent = BaseCollisionComponent;

	// Create the StaticMeshComponent.
	PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
	
	// Turn physics on for the static mesh.
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetCollisionProfileName("PickupCollision");
	// Attach the StaticMeshComponent to the RootComponent.
	PickupMesh->AttachTo(RootComponent);
}

void APickup::OnPickedUp_Implementation(AMOOnshineWorksCharacter *Actor)
{
	// There is no default behavior for a Pickup when it is picked up.
}


