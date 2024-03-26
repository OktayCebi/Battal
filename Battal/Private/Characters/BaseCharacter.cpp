// Battal


#include "Characters/BaseCharacter.h"

#include "Components/BoxComponent.h"


ABaseCharacter::ABaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	SetCharacterState(ECharacterState::ECS_Unarmed);
	SetActionState(EActionState::Eas_Idling);
	SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
	LastActionState = GetActionState();
	OverlappingItem = nullptr;
	Weapon = nullptr;
	IsGuarding = false;
	
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->SetupAttachment(GetMesh());
	Body->SetLeaderPoseComponent(GetMesh());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	Arms->SetupAttachment(GetMesh());
	Arms->SetLeaderPoseComponent(GetMesh());

	LightAttackComboCounter = 0;

	LightComboWaitTimes.Insert(0.5f, 0);
	
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

