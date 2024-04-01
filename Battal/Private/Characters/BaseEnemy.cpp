// Battal


#include "Characters/BaseEnemy.h"
#include "Characters/BattalCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Items/Weapons/WeaponBase.h"

ABaseEnemy::ABaseEnemy()
{
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);
	
	Target = nullptr;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if(UWorld* World = GetWorld())
	{
		Weapon = World->SpawnActor<AWeaponBase>(MainWeapon);
		const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->Body->AttachToComponent(GetMesh(), TransformRules, FName ("HandMainWeaponSocket"));
		Weapon->Sphere->DestroyComponent();
		KickCollisionBox->DestroyComponent();
		KickStartLocation->DestroyComponent();
		KickEndLocation->DestroyComponent();
		if(Weapon->SecondBody)
		{
		Weapon->SecondBody->AttachToComponent(GetMesh(), TransformRules, FName ("HandShieldSocket"));
		}
	}

	if(PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &ABaseEnemy::PawnSeen);
	}
}

void ABaseEnemy::PawnSeen(APawn* SeenPawn)
{
	Target = Cast<ABattalCharacter>(SeenPawn);
}
