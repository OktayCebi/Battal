// Battal


#include "Items/Weapons/WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Interfaces/HitInterface.h"

AWeaponBase::AWeaponBase()
{
	SelfStance = EWeaponStanceState::EwS_CommonStance;
	SecondBody = CreateDefaultSubobject<UStaticMeshComponent>("SecondBody");
	SecondBody->SetupAttachment(Body);
	SecondBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BodyWeaponBox = CreateDefaultSubobject<UBoxComponent>("BodyWeaponBox");
	BodyWeaponBox->SetupAttachment(Body);
	BodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyWeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	BodyWeaponBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	SecondBodyWeaponBox = CreateDefaultSubobject<UBoxComponent>("SecondBodyWeaponBox");
	SecondBodyWeaponBox->SetupAttachment(SecondBody);
	SecondBodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SecondBodyWeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	SecondBodyWeaponBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

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

	WeaponBaseDamage = 35.f;
	
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	BodyWeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBodyWeaponBoxOverlap);
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

void AWeaponBase::OnBodyWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BodyStartLocation->GetComponentLocation();
	const FVector End = BodyEndLocation->GetComponentLocation();
	const FVector TraceSize = BodyWeaponBox->GetUnscaledBoxExtent();
	TArray<AActor*> ActorsToIgnore;
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	ActorsToIgnore.Add(this);
	FHitResult BodyWeaponBoxHit;
	
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TraceSize,
		BodyStartLocation->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BodyWeaponBoxHit,
		true
	);

	if (BodyWeaponBoxHit.GetActor())
	{
		if(IHitInterface* HitInterface = Cast<IHitInterface>(BodyWeaponBoxHit.GetActor()))
		{
			HitInterface->GetHit(WeaponBaseDamage, BodyWeaponBoxHit.ImpactPoint, BodyWeaponBoxHit.GetActor()->GetActorLocation(), BodyWeaponBoxHit.GetActor()->GetActorRotation(), GetActorLocation());
		}
		
		IgnoreActors.AddUnique(BodyWeaponBoxHit.GetActor());
	}
}

void AWeaponBase::OnSecondBodyWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = SecondBodyStartLocation->GetComponentLocation();
	const FVector End = SecondBodyEndLocation->GetComponentLocation();
	const FVector TraceSize = SecondBodyWeaponBox->GetUnscaledBoxExtent();
	TArray<AActor*> ActorsToIgnore;
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	ActorsToIgnore.Add(this);
	FHitResult SecondBodyWeaponBoxHit;
	
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TraceSize,
		BodyStartLocation->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Persistent,
		SecondBodyWeaponBoxHit,
		true
	);

	if (SecondBodyWeaponBoxHit.GetActor())
	{
		if(IHitInterface* HitInterface = Cast<IHitInterface>(SecondBodyWeaponBoxHit.GetActor()))
		{
			HitInterface->GetHit(WeaponBaseDamage, SecondBodyWeaponBoxHit.ImpactPoint, SecondBodyWeaponBoxHit.GetActor()->GetActorLocation(), SecondBodyWeaponBoxHit.GetActor()->GetActorRotation(), GetActorLocation());
		}

		IgnoreActors.AddUnique(SecondBodyWeaponBoxHit.GetActor());
	} 
}

