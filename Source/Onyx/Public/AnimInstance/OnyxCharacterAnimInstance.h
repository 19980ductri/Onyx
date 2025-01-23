// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxAnimInstanceBase.h"
#include "Animation/AnimNodeReference.h"
#include "OnyxCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AOnyxCharacterBase;


UENUM(Blueprintable, BlueprintType)
enum class ERotationMode : uint8
{
	OrientationToMovement,
	Strafing
};

UENUM(Blueprintable, BlueprintType)
enum class EMovementState : uint8
{
	Idle,
	Moving
};

UENUM(Blueprintable, BlueprintType)
enum class EAnimMovementMode : uint8
{
	OnGround,
	InAir,
	None
};



UCLASS()
class ONYX_API UOnyxCharacterAnimInstance : public UOnyxAnimInstanceBase
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	
protected:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(BlueprintThreadSafe = "true"))
	FVector CalculateRelativeAccelerationAmount() const;

	virtual void UpdateStates();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector VelocityLastFrame;

	UPROPERTY(BlueprintReadWrite, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FAnimNodeReference OffsetNode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector VelocityAcceleration;
	
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
	ERotationMode CurrentRotationMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	ERotationMode LastFrameRotationMode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EMovementState  CurrentMovementState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EMovementState LastFrameMovementState;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EAnimMovementMode CurrentMovementMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EAnimMovementMode  LastFrameMovementMode;


	
	UPROPERTY()
	AOnyxCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovementComponent;
		

	FTransform CharacterTransform;
	FTransform LastFrameCharacterTransform;

	FTransform RootTransform;
	
	

	
};
