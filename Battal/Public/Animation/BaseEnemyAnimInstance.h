// Battal

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseEnemyAnimInstance.generated.h"

class UCharacterMovementComponent;
class ABaseEnemy;
/**
 * 
 */
UCLASS()
class BATTAL_API UBaseEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABaseEnemy> EnemyCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> EnemyMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFallingC;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float IsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsGuarding;
	
};
