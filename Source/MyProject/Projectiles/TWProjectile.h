#pragma once
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TWProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ATWProjectile : public AActor
{
	GENERATED_BODY()
public:
	ATWProjectile();


	
	
public:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	//int ProjectileMovementComponent;


	
	protected:
	UFUNCTION()
	void OnBounce (const FHitResult& ImpactResult, const FVector& impactVelocity);
};
