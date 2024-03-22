// Battal


#include "Items/Weapons/GreatSword.h"

AGreatSword::AGreatSword()
{
	SelfStance = EWeaponStanceState::EwS_GreatSwordStance;

	EquipSeconds = 0.42f;
	UnArmSeconds = 0.65f;

	HandSocketNameforBody = ("GreatSwordHandSocket");
	SheatSocketNameforBody = ("GreatSwordSheatSocket");
	EquipMontageSectionName = ("GreatSwordSection");
}

void AGreatSword::PickedUp(USceneComponent* InParent, FName InSocketName, FName InSocketNameSecond)
{
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	Body->AttachToComponent(InParent, TransformRules, InSocketName);
	SecondBody->DestroyComponent();
}
