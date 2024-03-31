// Battal


#include "Animation/BaseEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/BaseEnemy.h"

void UBaseEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyCharacter = Cast<ABaseEnemy>(TryGetPawnOwner());
	if(EnemyCharacter)
	{
		EnemyMovement = EnemyCharacter->GetCharacterMovement();
	}
}

void UBaseEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (EnemyMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(EnemyMovement->Velocity);
		IsFallingC = EnemyMovement->IsFalling();
		IsGuarding = EnemyCharacter->IsGuarding;
		IsAccelerating = UKismetMathLibrary::VSizeXY(EnemyMovement->GetCurrentAcceleration());
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
