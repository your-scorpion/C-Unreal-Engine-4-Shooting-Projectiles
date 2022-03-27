#include "TWCanonBox.h"
#include "Components/BoxComponent.h"
#include "MyProject/Player/TWPlayerPawn.h"

ATWCanonBox::ATWCanonBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(BoxComponent);

	BoxComponent -> OnComponentBeginOverlap.AddDynamic(this, &ATWCanonBox::OnBeginOverlap);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	MeshComponent -> SetupAttachment(BoxComponent);
}

void ATWCanonBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto pawn = Cast<ATWPlayerPawn>(OtherActor))
	{
		pawn -> SetCanon(CanonClass);
		//Destroy();
	}
}
