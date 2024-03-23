// Battal


#include "Characters/BaseCharacter.h"


ABaseCharacter::ABaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	SetCharacterState(ECharacterState::ECS_Unarmed);
	SetActionState(EActionState::Eas_Idling);
	SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
	LastActionState = GetActionState();
	OverlappingItem = nullptr;
	Weapon = nullptr;

	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->SetupAttachment(GetMesh());

	Body->SetLeaderPoseComponent(GetMesh());
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

