

#pragma once
#include "TWGun.h"
#include "Components/ArrowComponent.h" 
#include "Kismet/KismetArrayLibrary.h"
#include "TWTraceCanon.generated.h"


UCLASS()

class ATWTraceCanon : public ATWGun
{
	GENERATED_BODY()
public:
	virtual void DoFire() override;

public:
	UPROPERTY(EditAnywhere)
	float TraceDistance = 1000.f;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere)
	bool bDrawDebugTrace = false;
};

