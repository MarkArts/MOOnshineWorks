// Creative Common Share Alike

#pragma once

#include "DebuffManager.h"
#include "SuperJumpDebuff.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHINEWORKS_API ASuperJumpDebuff : public ADebuffManager
{
	GENERATED_UCLASS_BODY()

	virtual void SetDebuff(AActor* Target) override;
	virtual void QuitDebuff() override;
	
	
	
};
