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

	UFUNCTION()
	virtual void PickedUp (USceneComponent* InParent, FName InSocketName, FName InSocketNameSecond);

	UPROPERTY()
	EWeaponStanceState SelfStance;

	UPROPERTY(EditAnywhere, Category="Essentials")
	TObjectPtr<UStaticMeshComponent> SecondBody;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> EquipWeaponMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> UnArmWeaponMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> LightAttackMontage;

	UPROPERTY()
	int32 LightAttackComboCounter;

	UPROPERTY()
	float EquipSeconds;

	UPROPERTY()
	float UnArmSeconds;

	UPROPERTY()
	FName HandSocketNameforBody;

	UPROPERTY()
	FName HandSocketNameforSecondBody;

	UPROPERTY()
	FName SheatSocketNameforBody;

	UPROPERTY()
	FName SheatSocketNameforSecondBody;

	UPROPERTY()
	FName EquipMontageSectionName;
	
protected:
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
};
