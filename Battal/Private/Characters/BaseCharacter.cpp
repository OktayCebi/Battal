// Battal


#include "Characters/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
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
	}
}

void ABaseCharacter::EnableKickBoxCollision()
{
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABaseCharacter::DisableKickBoxCollision()
{
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	ActorsToIgnore.Add(this);
	FHitResult BodyWeaponBoxHit;
	
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
		BodyWeaponBoxHit,
		true
	);	
}

