#pragma once
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MyProject/Guns/TWGun.h"

#include "TWCanonBox.generated.h"


class ATWCanon;
class ATWGun;
class UBoxComponent;

UCLASS()
class ATWCanonBox : public AActor
{
	GENERATED_BODY()
public:
	ATWCanonBox();
	
public:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATWGun> CanonClass;

protected:
 	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
