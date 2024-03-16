// Battal

#pragma once

#include "CoreMinimal.h"
#include "Game/Status.h"
#include "Items/ItemBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTAL_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

	void PickedUp (USceneComponent* InParent, FName InSocketName, FName InSocketNameSecond);

	UPROPERTY()
	EWeaponStanceState SelfStance;
	
protected:

	UPROPERTY(EditAnywhere, Category="Essentials")
	TObjectPtr<UStaticMeshComponent> SecondBody;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
};
