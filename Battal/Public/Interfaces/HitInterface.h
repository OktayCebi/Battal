// Battal

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"


UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BATTAL_API IHitInterface
{
	GENERATED_BODY()

public:
	virtual void GetHit(const float& Damage, const FVector& ImpactPoint)  = 0;
};
