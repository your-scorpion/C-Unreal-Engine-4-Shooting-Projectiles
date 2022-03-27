#include "TWProjectile.h"

#include <ThirdParty/Vulkan/Include/vulkan/vulkan_core.h>

#include "GameFramework/ProjectileMovementComponent.h"

ATWProjectile::ATWProjectile()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>
		("ProjectileMovementComponent");

	ProjectileMovementComponent -> bShouldBounce = true;
	ProjectileMovementComponent -> OnProjectileBounce.AddDynamic(this, &ATWProjectile::OnBounce);
}

void ATWProjectile::OnBounce(const FHitResult& ImpactResult, const FVector& impactVelocity)
{
		Destroy();
}
