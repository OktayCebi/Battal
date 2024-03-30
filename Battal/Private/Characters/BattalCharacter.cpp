// Battal


#include "Characters/BattalCharacter.h"
#include "Components/BoxComponent.h"


ABattalCharacter::ABattalCharacter()
{
	LightAttackComboCounter = 3;

	LightComboWaitTimes.SetNum(3);
	LightComboWaitTimes.Insert(0.63f, 0);
	LightComboWaitTimes.Insert(0.89, 1);
	LightComboWaitTimes.Insert(0.91f, 2);
	
	KickCollisionBox->SetupAttachment(GetMesh(), FName ("KickCollisionBoxSocket"));
	KickStartLocation->SetupAttachment(KickCollisionBox);
	KickEndLocation->SetupAttachment(KickCollisionBox);
}

