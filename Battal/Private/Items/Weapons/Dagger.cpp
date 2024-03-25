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

	LightAttackComboCounter = 3;

	LightComboWaitTimes.SetNum(3);
	LightComboWaitTimes.Insert(0.44f, 0);
	LightComboWaitTimes.Insert(0.30, 1);
	LightComboWaitTimes.Insert(1.23f, 2);
}
