#include "TWGun.h"

ATWGun::ATWGun()
{
	TransformComponent = CreateDefaultSubobject<USceneComponent>("TransformComponent");
	SetRootComponent(TransformComponent);
	
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>("GunMesh");
	GunMesh -> SetupAttachment(TransformComponent);

	FirePoint = CreateDefaultSubobject<UArrowComponent>("FirePoint");
	FirePoint -> SetupAttachment(GunMesh);
}

void ATWGun::StartFire()
{
	GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Start Fire!"));

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ATWGun::DoFire, ReloadTime, true, 0.f); 
}

void ATWGun::StopFire()
{
	GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Stop Fire!"));

	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle); 
}


void ATWGun::DoFire()
{
	GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT(" Fire!"));	
}