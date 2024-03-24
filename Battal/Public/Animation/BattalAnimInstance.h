// Battal

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/BattalCharacter.h"
#include "BattalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTAL_API UBattalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABattalCharacter> BattalCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> BattalMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFallingC;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float IsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float StopDistance;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsGuarding;
	
};
