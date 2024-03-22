// Battal

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "GreatSword.generated.h"

/**
 * 
 */
UCLASS()
class BATTAL_API AGreatSword : public AWeaponBase
{
	GENERATED_BODY()

public:
	AGreatSword();
	
	virtual void PickedUp(USceneComponent* InParent, FName InSocketName, FName InSocketNameSecond) override;
};
