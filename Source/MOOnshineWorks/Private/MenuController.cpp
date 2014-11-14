// Fill out your copyright notice in the Description page of Project Settings.

#include "MOOnshineWorks.h"
#include "MenuPawn.h"
#include "MenuController.h"


AMenuController::AMenuController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AMenuController::SetMousePosition(float LocationX, float LocationY)
{
	FViewport* v = CastChecked<ULocalPlayer>(this->Player)->ViewportClient->Viewport;
	int intX = (int)LocationX;
	int intY = (int)LocationY;
	v->SetMouse(intX, intY);
}

AActor* AMenuController::getPointedObject(){
	APawn* pawn =  UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AMenuPawn* MenuPawn = (AMenuPawn*)pawn;
	
	UCameraComponent* Camera =  (*MenuPawn).FollowCamera.Get();
	FMinimalViewInfo ViewInfo = FMinimalViewInfo();
	Camera->GetCameraView(0.f, ViewInfo);

	FVector Location = ViewInfo.Location;
	FVector Rotation = ViewInfo.Rotation.Vector();

	FVector End = Location + Rotation * FVector(3000.f, 3000.f, 3000.f);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = false;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
 
	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);
     
	//call GetWorld() from within an actor extending class
	if (GetWorld()->LineTraceSingle(
		RV_Hit,        //result
		Location,    //start
		End, //end
		ECC_MAX, //collision channel
		RV_TraceParams
		)){

		return  RV_Hit.Actor.Get();;

	}
 
	return NULL;
}