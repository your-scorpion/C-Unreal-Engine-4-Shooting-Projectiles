// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TWPlayerPawn.generated.h"

class ATWGun;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MYPROJECT_API ATWPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ATWPlayerPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartFire();
	void StopFire();

	void SetCanon(TSubclassOf<ATWGun> CanonClass);
  
public:
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 512.f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveAcceleration = 1024.f;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationSpeed = 121.f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float RotationAcceleration = 47.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATWGun> DefaultCanonClass;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent * GunPivotComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;


protected:

	void PerformMovement(float DeltaTime);
	void PerformTurretRotation();
	void OnMoveForwardInput(float AxisValue);
	void OnMoveRightInput(float AxisValue);

	
private:
	UPROPERTY();
	ATWGun* Gun;
	
	float CurrentMoveSpeed = 0.f;
	float CurrentRotationSpeed = 0.f;
	
	float MoveForwardInput;
	float MoveRightInput;
};