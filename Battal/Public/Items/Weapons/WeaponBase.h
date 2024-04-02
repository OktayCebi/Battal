// Battal

#pragma once

#include "CoreMinimal.h"
#include "Game/Status.h"
#include "Items/ItemBase.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
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

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> LightHitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> HeavyHitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> GuardHitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> GuardHeavyHitReactMontage;

	UPROPERTY()
	int32 LightAttackComboCounter;

	UPROPERTY()
	TArray<float> LightComboWaitTimes;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Properties")
	TObjectPtr<UBoxComponent> BodyWeaponBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Properties")
	TObjectPtr<UBoxComponent> SecondBodyWeaponBox;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> BodyStartLocation;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> BodyEndLocation;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> SecondBodyStartLocation;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> SecondBodyEndLocation;

	UPROPERTY(VisibleAnywhere, Category="Weapon Attributes")
	float WeaponBaseDamage;

	UPROPERTY()
	TArray<AActor*> IgnoreActors;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
/**
	UFUNCTION()
	virtual void OnBodyWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnSecondBodyWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	*/
};
