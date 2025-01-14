// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxAnimInstanceBase.h"
#include "OnyxCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AOnyxCharacterBase;


UENUM(Blueprintable, BlueprintType)
enum ERotationMode
{
	OrientationToMovement,
	Strafing
};

UENUM(Blueprintable, BlueprintType)
enum EMovementState
{
	Idle,
	Moving
};



UCLASS()
class ONYX_API UOnyxCharacterAnimInstance : public UOnyxAnimInstanceBase
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	
protected:

	void UpdateMovementState();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector VelocityLastFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector Acceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector AccelerationLastFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	bool bHasAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float LocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ERotationMode> RotationMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EMovementState> MovementState;
	
	
	UPROPERTY()
	AOnyxCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovement;
	
	
};
