// Battal

#include "Animation/BattalAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BattalCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UBattalAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BattalCharacter = Cast<ABattalCharacter>(TryGetPawnOwner());
	if (BattalCharacter)
	{
		BattalMovement = BattalCharacter->GetCharacterMovement();
	}
}

void UBattalAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (BattalMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(BattalMovement->Velocity);
		IsFallingC = BattalMovement->IsFalling();
		IsGuarding = BattalCharacter->IsGuarding;
		IsAccelerating = UKismetMathLibrary::VSizeXY(BattalMovement->GetCurrentAcceleration());
		if(UKismetMathLibrary::NearlyEqual_FloatFloat(IsAccelerating, 0.f, 0.001f))
		{
			bIsAccelerating = false;
		}
		else
		{
			bIsAccelerating = true;
		}
	}
	
}
