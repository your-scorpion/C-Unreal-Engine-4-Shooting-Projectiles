
#include "TWTraceCanon.h"
#include "Components/ArrowComponent.h"
#include "TWGun.h"
#include "Kismet/KismetSystemLibrary.h"




void ATWTraceCanon::DoFire()
{
	const FVector startTrace = FirePoint -> GetComponentLocation();
	const FVector endTrace = startTrace + (FirePoint -> GetForwardVector() * TraceDistance);	

	const EDrawDebugTrace::Type DrawDebugType = bDrawDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	FHitResult hitResult;
	
	UKismetSystemLibrary::LineTraceSingle(this, startTrace, endTrace, TraceChannel, false, {}, DrawDebugType, hitResult, true);
}

/*
void ATWTraceCanon::DoFire()
{
	Super::DoFire();
}
*/
