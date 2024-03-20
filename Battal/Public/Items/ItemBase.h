// Battal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;

UCLASS()
class BATTAL_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	UPROPERTY(EditAnywhere, Category="Essentials")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(EditAnywhere, Category="Essentials")
	TObjectPtr<USphereComponent> Sphere;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	
	virtual void Tick(float DeltaTime) override;
	

};
