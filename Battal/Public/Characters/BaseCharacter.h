// Battal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Game/Status.h"
#include "BaseCharacter.generated.h"

class AWeaponBase;
class AItemBase;
UCLASS()
class BATTAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	UPROPERTY()
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY()
	TObjectPtr<AWeaponBase> Weapon;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DodgeMontage;

	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Movement | CharacterState")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly)
	EActionState ActionState;

	UPROPERTY(BlueprintReadOnly)
	EActionState LastActionState;

	UPROPERTY(BlueprintReadOnly)
	EWeaponStanceState WeaponStanceState;
	
public:
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState;}
	FORCEINLINE ECharacterState SetCharacterState(ECharacterState const NewState) {return CharacterState = NewState;}
	FORCEINLINE EActionState GetActionState() const {return ActionState;}
	FORCEINLINE EActionState SetActionState(EActionState const NewState) {return ActionState = NewState;}
	FORCEINLINE EActionState GetLastActionState() const {return ActionState;}
	FORCEINLINE EWeaponStanceState GetWeaponStanceState() const {return WeaponStanceState;}
	FORCEINLINE EWeaponStanceState SetWeaponStanceState(EWeaponStanceState const NewStance) {return WeaponStanceState = NewStance;}
	FORCEINLINE void SetOverlappingItem(AItemBase* NewItem) {OverlappingItem = NewItem;}
	FORCEINLINE void SetWeapon(AWeaponBase* NewWeapon) {Weapon = NewWeapon;}
};
