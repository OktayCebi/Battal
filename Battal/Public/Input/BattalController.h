// Battal

#pragma once

#include "CoreMinimal.h"
#include "Characters/BattalCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Game/Status.h"
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
	int32 WeaponIndex;

	UPROPERTY(BlueprintReadOnly)
	int32 IndexCounter;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	////////////Timers//////////////
	UPROPERTY()
	FTimerHandle DodgeTimerHandle;
	UPROPERTY(BlueprintReadOnly)
	float EndDodgeTimeAmount;
	////////////Timers//////////////

private:

	UPROPERTY()
	EActionState LastActionState;
	///////////////////INPUT ACTIONS AND BIND FUNCTIONS////////////////
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

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> StopSprintAction;

	void StopSprint();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	void Interact();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EquipDaggerAction;

	void EquipDagger();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EquipAxeAction;

	void EquipAxe();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EquipDenemeAction;

	void EquipDeneme();
	
	FTimerHandle EquipHandle;
	UFUNCTION()
	void EquipAttachFunction();
	UFUNCTION()
	void UnArmAttachFunction();
	///////////////////INPUT ACTIONS AND BIND FUNCTIONS////////////////

	////////////////DODGE SECTION///////////////////
	void ZeroDodgeMontageNumber();
	void Dodge();
	void EndDodge();
	UFUNCTION()
	FORCEINLINE bool CanDodgeWithWeapon() {return BattalCharacter->GetActionState() != EActionState::Eas_Dodging && BattalCharacter->Weapon && BattalCharacter->GetCharacterState() == ECharacterState::ECS_Equipped;}
	FORCEINLINE bool CanDodge() {return BattalCharacter->GetActionState() != EActionState::Eas_Dodging;}
	UPROPERTY()
	int32 DodgeMontageNumber;
	UPROPERTY()
	FVector2D ForVec;
	////////////////DODGE SECTION///////////////////
	
};
