// Battal


#include "Items/Weapons/WeaponBase.h"

#include "Components/BoxComponent.h"

AWeaponBase::AWeaponBase()
{
	SelfStance = EWeaponStanceState::EwS_CommonStance;
	SecondBody = CreateDefaultSubobject<UStaticMeshComponent>("SecondBody");
	SecondBody->SetupAttachment(Body);
	SecondBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BodyWeaponBox = CreateDefaultSubobject<UBoxComponent>("BodyWeaponBox");
	BodyWeaponBox->SetupAttachment(Body);

	SecondBodyWeaponBox = CreateDefaultSubobject<UBoxComponent>("SecondBodyWeaponBox");
	SecondBodyWeaponBox->SetupAttachment(SecondBody);

	BodyStartLocation = CreateDefaultSubobject<USceneComponent>("BodyStartLocation");
	BodyEndLocation = CreateDefaultSubobject<USceneComponent>("BodyEndLocation");
	SecondBodyStartLocation = CreateDefaultSubobject<USceneComponent>("SecondBodyStartLocation");
	SecondBodyEndLocation = CreateDefaultSubobject<USceneComponent>("SecondBodyEndLocation");

	BodyStartLocation->SetupAttachment(BodyWeaponBox);
	BodyEndLocation->SetupAttachment(BodyWeaponBox);
	SecondBodyStartLocation->SetupAttachment(SecondBodyWeaponBox);
	SecondBodyEndLocation->SetupAttachment(SecondBodyWeaponBox);
	

	EquipSeconds = 0.f;
	UnArmSeconds = 0.f;
	LightAttackComboCounter = 0;

	LightComboWaitTimes.Insert(0.50f, 0);
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
