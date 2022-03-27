#include "TWProjectileCanon.h"
#include "Components/ArrowComponent.h"
#include "MyProject/Projectiles/TWProjectile.h"

void ATWProjectileCanon::DoFire()
{
	if(ProjectileClass != nullptr)
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ATWProjectile* projectile = GetWorld() -> SpawnActor<ATWProjectile>(ProjectileClass, FirePoint -> GetComponentLocation(), FirePoint -> GetComponentRotation(), actorSpawnParameters);

	}
	else
	{
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ATWProjectile:ProjectileClass is null!"));
	}
}	 
	