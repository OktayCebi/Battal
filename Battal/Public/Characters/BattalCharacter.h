// Battal

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BattalCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTAL_API ABattalCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABattalCharacter();

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> EquipWeaponMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> UnArmWeaponMontage;
	
};
