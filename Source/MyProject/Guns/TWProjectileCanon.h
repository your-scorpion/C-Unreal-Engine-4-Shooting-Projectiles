#pragma once
#include "TWGun.h"
#include "TWProjectileCanon.h"
#include "TWProjectileCanon.generated.h"



class ATWProjectile;
UCLASS()
class ATWProjectileCanon : public ATWGun
{
	GENERATED_BODY()
public:
	virtual void DoFire() override; 



public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATWProjectile> ProjectileClass;
};