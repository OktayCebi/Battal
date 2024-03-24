// Battal


#include "Items/Weapons/Dagger.h"

ADagger::ADagger()
{
	SelfStance = EWeaponStanceState::EwS_DaggerStance;

	EquipSeconds = 0.28f;
	UnArmSeconds = 0.60f;

	HandSocketNameforBody = ("WeaponRightHandSocket");
	HandSocketNameforSecondBody = ("WeaponLeftHandSocket");
	SheatSocketNameforBody = ("RightDaggerSocket");
	SheatSocketNameforSecondBody = ("LeftDaggerSocket");
	EquipMontageSectionName = ("DaggerSection");
}