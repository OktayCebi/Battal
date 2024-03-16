// Battal


#include "Items/Weapons/WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	SelfStance = EWeaponStanceState::EwS_CommonStance;
	SecondBody = CreateDefaultSubobject<UStaticMeshComponent>("SecondBody");
	SecondBody->SetupAttachment(Body);
	SecondBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EquipSeconds = 0.f;
	UnArmSeconds = 0.f;
}

void AWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}

void AWeaponBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeaponBase::PickedUp(USceneComponent* InParent, const FName InSocketName, const FName InSocketNameSecond)
{
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	Body->AttachToComponent(InParent, TransformRules, InSocketName);
	SecondBody->AttachToComponent(InParent, TransformRules, InSocketNameSecond);
	
}
