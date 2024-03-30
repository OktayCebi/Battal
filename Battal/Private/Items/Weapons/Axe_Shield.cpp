// Battal


#include "Items/Weapons/Axe_Shield.h"

AAxe_Shield::AAxe_Shield()
{
	SelfStance = EWeaponStanceState::EwS_AxeStance;

	EquipSeconds = 0.28f;
	UnArmSeconds = 0.77f;

	HandSocketNameforBody = ("AxeHandSocket");
	HandSocketNameforSecondBody = ("ShieldHandSocket");
	SheatSocketNameforBody = ("AxeSheatSocket");
	SheatSocketNameforSecondBody = ("ShieldSheatSocket");
	EquipMontageSectionName = ("AxeSection");

	LightAttackComboCounter = 4;

	LightComboWaitTimes.SetNum(4);
	LightComboWaitTimes.Insert(0.70f, 0);
	LightComboWaitTimes.Insert(0.66f, 1);
	LightComboWaitTimes.Insert(0.77f, 2);
	LightComboWaitTimes.Insert(1.69f, 3);
}
