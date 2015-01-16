// Creative Common Share Alike

#include "MOOnshineWorks.h"
#include "SuperJumpDebuff.h"


ASuperJumpDebuff::ASuperJumpDebuff(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	DebuffType = "SuperJump";
	DebuffTime = 12.f;
}

void ASuperJumpDebuff::SetDebuff(AActor* Target){
	if (IsValid(this)) {
		DebuffsActive.Add(this);
		AMOOnshineWorksCharacter* CharTarget = Cast<AMOOnshineWorksCharacter>(Target);
		CharTarget->CharacterMovement->JumpZVelocity *= 3;
		SetTime(DebuffTime);
	}
}

void ASuperJumpDebuff::QuitDebuff(){
	AMOOnshineWorksCharacter* Player = (AMOOnshineWorksCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->CharacterMovement->JumpZVelocity /= 3;
	DebuffsActive.Remove(this);
}


