// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxAnimInstanceBase.h"
#include "OnyxCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AOnyxCharacterBase;
/**
 * 
 */
UCLASS()
class ONYX_API UOnyxCharacterAnimInstance : public UOnyxAnimInstanceBase
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	bool bHasAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float LocomotionDirection;

	UPROPERTY()
	AOnyxCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovement;
	
	
};
