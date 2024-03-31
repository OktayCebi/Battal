// Battal

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BATTAL_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ABaseEnemy();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Enemy")
	TSubclassOf<AWeaponBase> MainWeapon;
	
};
