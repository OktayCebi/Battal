// Battal

#pragma once

#include "CoreMinimal.h"
#include "Characters/BattalCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Game/Status.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BattalController.generated.h"

class ABattalCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class BATTAL_API ABattalController : public APlayerController
{
	GENERATED_BODY()

public:
	ABattalController();

	UPROPERTY()
	TObjectPtr<ABattalCharacter> BattalCharacter;

	UPROPERTY(BlueprintReadOnly)
	EActionState LastActionState;

	

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	
		///////////////////MOVEMENT and INTERACT SECTION////////////////
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	void Look(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SprintAction;

	void Sprint();

	void StopSprint();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	void Interact();
	
	///////////////////MOVEMENT and INTERACT SECTION////////////////

	////////////////DODGE SECTION///////////////////
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DodgeAction;
	void ZeroDodgeMontageNumber();
	void Dodge();
	void EndDodge();
	UFUNCTION()
	FORCEINLINE bool CanDodgeWithWeapon() {return BattalCharacter->GetActionState() != EActionState::Eas_Dodging && BattalCharacter->GetCharacterState() == ECharacterState::ECS_Equipped && BattalCharacter->GetActionState() != EActionState::Eas_Attacking && BattalCharacter->GetMovementComponent()->IsFalling() == false;}
	FORCEINLINE bool CanDodge() {return BattalCharacter->GetActionState() != EActionState::Eas_Dodging && BattalCharacter->GetActionState() != EActionState::Eas_Attacking && BattalCharacter->GetMovementComponent()->IsFalling() == false;}
	UPROPERTY()
	int32 DodgeMontageNumber;
	UPROPERTY()
	FVector2D ForVec;
	UPROPERTY()
	///Timers///
	FTimerHandle DodgeTimerHandle;
	UPROPERTY()
	float EndDodgeTimeAmount;
	////////////////DODGE SECTION///////////////////
	
	////////////////EQUIP SECTION///////////////////
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EquipAction;
	void Equip();
	UPROPERTY()
	int32 WeaponIndex;
	///Timers///
	FTimerHandle EquipHandle;
	UFUNCTION()
	void EquipAttachFunction();
	UFUNCTION()
	void UnArmAttachFunction();
	////////////////EQUIP SECTION///////////////////
	
	////////////////GUARD SECTION//////////////////
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> GuardAction;
	void Guard();
	void ExitGuard();
	bool CanGuard() {return BattalCharacter->GetActionState() != EActionState::Eas_Attacking && BattalCharacter->GetActionState() != EActionState::Eas_Dodging;}
	////////////////GUARD SECTION//////////////////

	
	////////////LIGHT ATTACK SECTION///////////////
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LightAttackAction;
	void LightAttack();
	FORCEINLINE bool CanAttack() {return BattalCharacter->GetActionState() != EActionState::Eas_Dodging && BattalCharacter->GetActionState() != EActionState::Eas_Attacking;}
	UPROPERTY()
	int32 LightAttackCounter;
	UPROPERTY()
	bool WasAttackSaved;
	FTimerHandle EndAttackTimerHandle;
	void EndLightAttack();
	
};
