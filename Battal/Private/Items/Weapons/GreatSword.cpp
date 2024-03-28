// Battal


#include "Items/Weapons/GreatSword.h"

#include "Components/BoxComponent.h"

AGreatSword::AGreatSword()
{
	SelfStance = EWeaponStanceState::EwS_GreatSwordStance;

	EquipSeconds = 0.42f;
	UnArmSeconds = 0.65f;

	HandSocketNameforBody = ("GreatSwordHandSocket");
	SheatSocketNameforBody = ("GreatSwordSheatSocket");
	EquipMontageSectionName = ("GreatSwordSection");

	LightAttackComboCounter = 3;

	LightComboWaitTimes.SetNum(3);
	LightComboWaitTimes.Insert(1.55f, 0);
	LightComboWaitTimes.Insert(1.75, 1);
	LightComboWaitTimes.Insert(2.59f, 2);
}

void AGreatSword::PickedUp(USceneComponent* InParent, FName InSocketName, FName InSocketNameSecond)
{
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	Body->AttachToComponent(InParent, TransformRules, InSocketName);
	SecondBody->DestroyComponent();
	SecondBodyWeaponBox->DestroyComponent();
	SecondBodyEndLocation->DestroyComponent();
	SecondBodyStartLocation->DestroyComponent();
}
