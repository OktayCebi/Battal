// Battal


#include "Items/ItemBase.h"
#include "Characters/BattalCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	
	SetRootComponent(Body);
	Sphere->SetupAttachment(Body);

	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetGenerateOverlapEvents(true);
	

}


void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnSphereEndOverlap);
}


void AItemBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABattalCharacter* BattalCharacter = Cast<ABattalCharacter>(OtherActor))
	{
		BattalCharacter->SetOverlappingItem(this);
	}
}

void AItemBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(ABattalCharacter* BattalCharacter = Cast<ABattalCharacter>(OtherActor))
	{
		BattalCharacter->SetOverlappingItem(nullptr);
	}
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

