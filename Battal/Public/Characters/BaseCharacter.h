// Battal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Game/Status.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;
class AWeaponBase;
class AItemBase;
UCLASS()
class BATTAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	UPROPERTY(BlueprintReadOnly)
	bool IsGuarding;

	UPROPERTY()
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AWeaponBase> Weapon;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(BlueprintReadOnly)
	TArray<AWeaponBase*> Weapons;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Body;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> LightAttackMontage;

	UPROPERTY()
	int32 LightAttackComboCounter;

	UPROPERTY()
	TArray<float> LightComboWaitTimes;


	
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
