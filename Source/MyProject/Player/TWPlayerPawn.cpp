// Fill out your copyright notice in the Description page of Project Settings.


#include "TWPlayerPawn.h"

#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProject/Guns/TWGun.h"
#include "MyProject/MyProject.h"

// Sets default values
ATWPlayerPawn::ATWPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(BoxComponent);
	
	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BodyMeshComponent");
	SetRootComponent(BodyMeshComponent);
	
	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TurretMeshComponent");
	TurretMeshComponent -> SetupAttachment(BodyMeshComponent);

	GunPivotComponent = CreateDefaultSubobject<UArrowComponent>("GunPivotComponent");
	GunPivotComponent -> SetupAttachment(TurretMeshComponent);

	SpringArmComponent= CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");//откуда рендер будет произведен
	SpringArmComponent -> SetupAttachment(BodyMeshComponent);

	FollowCamera= CreateDefaultSubobject<UCameraComponent>("FollowCamera");//отвечает за рендер
	FollowCamera -> SetupAttachment(SpringArmComponent);

	//USpringArmComponent* SpringArmComponent;


	//UCameraComponent* FollowCamera;

	//UStaticMeshComponent* TurretMeshComponent;

}

void ATWPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	SetCanon(DefaultCanonClass);
	if (DefaultCanonClass != nullptr)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Gun = GetWorld()-> SpawnActor<ATWGun>(DefaultCanonClass, GunPivotComponent -> GetComponentLocation(), GunPivotComponent->GetComponentRotation(), spawnParams);

		Gun -> AttachToComponent(GunPivotComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void ATWPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMovement(DeltaTime);
	if(const auto controller = Cast<APlayerController>(GetController()))
	{
		float mouseX, mouseY;
		controller -> GetMousePosition(mouseX, mouseY);

		FVector mouseLocation, mouseDirection;
		controller -> DeprojectScreenPositionToWorld(mouseX, mouseY, mouseLocation, mouseDirection);

		GEngine -> AddOnScreenDebugMessage (-1, 0.f, FColor::Orange, FString::Printf(TEXT("Mouse x: %.2f, y:%.2f"), mouseX, mouseY));

		DrawDebugSphere(GetWorld(), mouseLocation, 12.f, 36, FColor::Green);

		FVector correctMouseLocation = mouseLocation;

		const FVector actorLocation = GetActorLocation();
		//correctMouseLocation.Z = actorLocation.Z;

		float distance = FVector::Distance(actorLocation, mouseLocation);
		
		
		FVector correctMouseDirection = mouseLocation - FollowCamera-> GetComponentLocation();
		correctMouseDirection.Normalize();

		correctMouseLocation = mouseLocation + (correctMouseDirection * 1000.f);
		correctMouseLocation.Z = actorLocation.Z;
		DrawDebugLine(GetWorld(), actorLocation, correctMouseLocation, FColor::Green, false, 0.f, 0, 5.f);

		FRotator newTurretRotation =  UKismetMathLibrary::FindLookAtRotation(TurretMeshComponent -> GetComponentLocation(), correctMouseLocation);
		newTurretRotation.Roll= TurretMeshComponent -> GetComponentRotation().Roll;
		newTurretRotation.Pitch= TurretMeshComponent -> GetComponentRotation().Pitch;
		TurretMeshComponent -> SetWorldRotation(newTurretRotation);
	}
}

void ATWPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent -> BindAction()
	PlayerInputComponent -> BindAxis("MoveForward", this, &ATWPlayerPawn::OnMoveForwardInput);
	PlayerInputComponent -> BindAxis("MoveRight", this, &ATWPlayerPawn::OnMoveRightInput);

	PlayerInputComponent -> BindAction("Fire", EInputEvent::IE_Pressed, this, &ATWPlayerPawn::StartFire);
	PlayerInputComponent -> BindAction("Fire", EInputEvent::IE_Released, this, &ATWPlayerPawn::StopFire);
}

void ATWPlayerPawn::StartFire()
{
	if(Gun != nullptr)
	{
		Gun->StartFire();
	}
	else
	{
		UE_LOG(LogTW, Error, TEXT("Gun is Null!"));
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Gun is Null!!"));
	}
}


void ATWPlayerPawn::StopFire()
{
	if(Gun != nullptr)
	{
		Gun->StopFire();
	}
}





void ATWPlayerPawn::SetCanon(TSubclassOf<ATWGun> CanonClass)
{
	if (CanonClass != nullptr)
	{

		if(Gun != nullptr)
		{
			Gun -> Destroy();
		}
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Gun = GetWorld()-> SpawnActor<ATWGun>(CanonClass, GunPivotComponent -> GetComponentLocation(), GunPivotComponent->GetComponentRotation(), spawnParams);

		Gun -> AttachToComponent(GunPivotComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}





void ATWPlayerPawn::PerformMovement(float DeltaTime)
{

	if(FMath::IsNearlyZero(MoveForwardInput))
	{
		CurrentMoveSpeed = 0.f;
	}

	else
	{
		CurrentMoveSpeed = FMath::FInterpConstantTo(CurrentMoveSpeed, MoveSpeed * FMath::Abs(MoveForwardInput), DeltaTime, MoveAcceleration);
		const FVector moveDelta = GetActorForwardVector() * CurrentMoveSpeed * DeltaTime * FMath::Sign(MoveForwardInput);
		SetActorLocation(GetActorLocation() + moveDelta);	
	}
	//FVector location = GetActorLocation();
	//SetActorLocation(location);

	//FRotator rotation = GetActorRotation();
	
	if (FMath::IsNearlyZero(MoveRightInput)) {
		CurrentRotationSpeed = 0.f;
	}
	else
	{
		CurrentRotationSpeed = FMath::FInterpConstantTo(CurrentRotationSpeed, RotationSpeed * FMath::Abs(MoveRightInput), DeltaTime, RotationAcceleration);
		const FRotator rotationDelta = FRotator(0.f, CurrentRotationSpeed * DeltaTime * FMath::Sign(MoveRightInput), 0.f );
		SetActorRotation(GetActorRotation() + rotationDelta);
	}
		
}	


void ATWPlayerPawn::OnMoveForwardInput(float AxisValue)
{
	MoveForwardInput = AxisValue;
}


void ATWPlayerPawn::OnMoveRightInput(float AxisValue)
{
	MoveRightInput = AxisValue;
}
