// Battal


#include "Characters/BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"


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
	KickCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	KickCollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	KickCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	KickStartLocation = CreateDefaultSubobject<USceneComponent>("KickStartLocation");
	KickEndLocation = CreateDefaultSubobject<USceneComponent>("KickEndLocation");
	
	Body = CreateDefaultSubobject<USkeletalMeshComponent>("Body");
	Body->SetupAttachment(GetMesh());
	Body->SetLeaderPoseComponent(GetMesh());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	Arms->SetupAttachment(GetMesh());
	Arms->SetLeaderPoseComponent(GetMesh());

	LightAttackComboCounter = 0;

	LightComboWaitTimes.Insert(0.5f, 0);
	
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

