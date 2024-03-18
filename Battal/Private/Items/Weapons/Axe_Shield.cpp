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
}
