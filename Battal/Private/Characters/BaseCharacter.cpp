// Battal


#include "Characters/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HitInterface.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/WeaponBase.h"


ABaseCharacter::ABaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	SetCharacterState(ECharacterState::ECS_Unarmed);
	SetActionState(EActionState::Eas_Idling);
	SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
	LastActionState = GetActionState();
	OverlappingItem = nullptr;
	Weapon = nullptr;
	IsGuarding = false;

	KickCollisionBox = CreateDefaultSubobject<UBoxComponent>("KickCollisionBox");
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KickCollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	KickCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	KickStartLocation = CreateDefaultSubobject<USceneComponent>("KickStartLocation");
	KickStartLocation->SetupAttachment(KickCollisionBox);
	KickEndLocation = CreateDefaultSubobject<USceneComponent>("KickEndLocation");
	KickEndLocation->SetupAttachment(KickCollisionBox);
	
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->SetupAttachment(GetMesh());
	Body->SetLeaderPoseComponent(GetMesh());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	Arms->SetupAttachment(GetMesh());
	Arms->SetLeaderPoseComponent(GetMesh());

	Legs = CreateDefaultSubobject<USkeletalMeshComponent>("Legs");
	Legs->SetupAttachment(GetMesh());
	Legs->SetLeaderPoseComponent(GetMesh());
	

	LightAttackComboCounter = 0;

	LightComboWaitTimes.Insert(0.5f, 0);

	MaxHealth = 100.f;
	Health = MaxHealth;
	MaxPosture = 100.f;
	Posture = MaxPosture;
	KickBaseDamage = 25.f;
}

void ABaseCharacter::EnableBoxCollision()
{
	if(Weapon)
	{
		Weapon->BodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ABaseCharacter::DisableBoxCollision()
{
	if(Weapon)
	{
		Weapon->BodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Weapon->IgnoreActors.Empty();
	}
}

void ABaseCharacter::EnableSecondBoxCollision()
{
	if(Weapon->SecondBodyWeaponBox)
	{
		Weapon->SecondBodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ABaseCharacter::DisableSecondBoxCollision()
{
	if(Weapon->SecondBodyWeaponBox)
	{
		Weapon->SecondBodyWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Weapon->IgnoreActors.Empty();
	}
}

void ABaseCharacter::EnableKickBoxCollision()
{
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABaseCharacter::DisableKickBoxCollision()
{
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IgnoreActors.Empty();
}


void ABaseCharacter::GetHit(const float& Damage, const FVector& ImpactPoint)
{
	if (GetActionState() == EActionState::Eas_Guarding)
	Posture = Posture - (Damage / 2.f);
	else
	{
		Health = Health - Damage;
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	KickCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnKickBoxOverlap);
}

void ABaseCharacter::OnKickBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = KickStartLocation->GetComponentLocation();
	const FVector End = KickEndLocation->GetComponentLocation();
	const FVector TraceSize = KickCollisionBox->GetUnscaledBoxExtent();
	TArray<AActor*> ActorsToIgnore;
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	ActorsToIgnore.Add(this);
	FHitResult KickBoxHit;
	
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		TraceSize,
		KickStartLocation->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		KickBoxHit,
		true
	);

	if (KickBoxHit.GetActor())
	{
		if(IHitInterface* HitInterface = Cast<IHitInterface>(KickBoxHit.GetActor()))
		{
			HitInterface->GetHit(KickBaseDamage, KickBoxHit.ImpactPoint);
		}
		IgnoreActors.AddUnique(KickBoxHit.GetActor());
	}
}

