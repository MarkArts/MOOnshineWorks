// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

USTRUCT(BlueprintType)
struct FDisplayString
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FString Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FVector2D Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	UFont* Font;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	FVector2D Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	int32 DisplayTime;

	int32 StartTime;
};

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMainHUD(const class FObjectInitializer& PCIP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	UFont* Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOO)
	TArray<FDisplayString> DisplayStrings;

	UFUNCTION(BlueprintCallable, Category = MOOnshine)
	void AddDisplayString(FDisplayString DisplayStringToAdd);

protected:
	void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;
};
