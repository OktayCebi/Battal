// Battal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Game/Status.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;
class AWeaponBase;
class AItemBase;
UCLASS()
class BATTAL_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	UPROPERTY(BlueprintReadOnly)
	bool IsGuarding;

	UPROPERTY()
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AWeaponBase> Weapon;

	UFUNCTION(BlueprintCallable)
	void EnableBoxCollision();

	UFUNCTION(BlueprintCallable)
	void DisableBoxCollision();

	UFUNCTION(BlueprintCallable)
	void EnableSecondBoxCollision();

	UFUNCTION(BlueprintCallable)
	void DisableSecondBoxCollision();

	UFUNCTION(BlueprintCallable)
	void EnableKickBoxCollision();

	UFUNCTION(BlueprintCallable)
	void DisableKickBoxCollision();

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> DodgeMontage;

	UPROPERTY(BlueprintReadOnly)
	TArray<AWeaponBase*> Weapons;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Body;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Legs;

	UPROPERTY(EditDefaultsOnly, Category="Montages")
	TObjectPtr<UAnimMontage> LightAttackMontage;

	UPROPERTY()
	int32 LightAttackComboCounter;

	UPROPERTY()
	TArray<float> LightComboWaitTimes;

	virtual void GetHit(const float& Damage, const FVector& ImpactPoint) override;

	static FName GetAngle(const FVector& SelfLocation, const FRotator& SelfRotation, const FVector& TargetLocation);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="CharacterBaseAttributes")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="CharacterBaseAttributes")
	float Health;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="CharacterBaseAttributes")
	float MaxPosture;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="CharacterBaseAttributes")
	float Posture;
	
	UPROPERTY(VisibleAnywhere, Category="CharacterBaseAttributes")
	float KickBaseDamage;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABaseCharacter> Target;

	UPROPERTY()
	TArray<AActor*> IgnoreActors;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Movement | CharacterState")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly)
	EActionState ActionState;

	UPROPERTY(BlueprintReadOnly)
	EActionState LastActionState;

	UPROPERTY(BlueprintReadOnly)
	EWeaponStanceState WeaponStanceState;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> KickCollisionBox;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> KickStartLocation;

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	TObjectPtr<USceneComponent> KickEndLocation;

	UFUNCTION()
	virtual void OnKickBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
/**
	UFUNCTION()
	static FName  GetAngle(const FVector& SelfLocation, const FRotator& SelfRotation, const FVector& TargetLocation);
*/
public:
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState;}
	FORCEINLINE ECharacterState SetCharacterState(ECharacterState const NewState) {return CharacterState = NewState;}
	FORCEINLINE EActionState GetActionState() const {return ActionState;}
	FORCEINLINE EActionState SetActionState(EActionState const NewState) {return ActionState = NewState;}
	FORCEINLINE EActionState GetLastActionState() const {return ActionState;}
	FORCEINLINE EWeaponStanceState GetWeaponStanceState() const {return WeaponStanceState;}
	FORCEINLINE EWeaponStanceState SetWeaponStanceState(EWeaponStanceState const NewStance) {return WeaponStanceState = NewStance;}
	FORCEINLINE void SetOverlappingItem(AItemBase* NewItem) {OverlappingItem = NewItem;}
	FORCEINLINE void SetWeapon(AWeaponBase* NewWeapon) {Weapon = NewWeapon;}
};
