#pragma once
//это аналог TWCanon.h
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

#include "TWGun.generated.h"

class UStaticMeshComponent;
 
UCLASS()
class ATWGun : public AActor
{
	GENERATED_BODY()
public: 
	ATWGun();

	void StartFire();
	void StopFire();


protected:
	virtual void DoFire();
	
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent * TransformComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * GunMesh;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* FirePoint; 

	UPROPERTY(EditAnywhere)
	float ReloadTime;

	FTimerHandle FireTimerHandle;
};

