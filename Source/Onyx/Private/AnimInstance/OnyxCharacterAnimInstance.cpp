// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxCharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Characters/OnyxCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOnyxCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AOnyxCharacterBase>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
	}
	
}

void UOnyxCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!OwningCharacter || !OwningCharacterMovement)
	{
		return;
	}
	RotationMode = ERotationMode::OrientationToMovement;
	AccelerationLastFrame = Acceleration;
	Acceleration = OwningCharacterMovement->GetCurrentAcceleration();
	
	VelocityLastFrame = Velocity;
	Velocity = OwningCharacterMovement->Velocity;
	VelocityAcceleration = (Velocity - VelocityLastFrame) / UKismetMathLibrary::FMax(DeltaSeconds, 0.001f);
	
	
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	
}

void UOnyxCharacterAnimInstance::UpdateMovementState()
{
	
}

FVector UOnyxCharacterAnimInstance::CalculateRelativeAccelerationAmount()
{
	if (OwningCharacterMovement == nullptr || OwningCharacter == nullptr)
	{
		return FVector(0, 0, 0);
	}
	FVector RelativeAcceleration;
	
	if (OwningCharacterMovement->MaxAcceleration < 0 && OwningCharacterMovement->GetMaxBrakingDeceleration() < 0
		/* || CurrentMovementMode == EAnimMovementMode::InAir*/)
	{
		return FVector(0, 0, 0);
	}
	const float DotValue = UKismetMathLibrary::Dot_VectorVector(Acceleration, Velocity);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("DotValue: %f"), DotValue));
	if (DotValue > 0)
	{
		const FVector MaxClampedVelocityAccel = UKismetMathLibrary::Vector_ClampSizeMax(VelocityAcceleration,OwningCharacterMovement->MaxAcceleration);
		RelativeAcceleration = UKismetMathLibrary::Quat_UnrotateVector(
			OwningCharacter->GetTransform().GetRotation(), MaxClampedVelocityAccel/OwningCharacterMovement->MaxAcceleration);
	
	}
	else
	{
		const FVector MaxClampedVelocityAccel = UKismetMathLibrary::Vector_ClampSizeMax(VelocityAcceleration,OwningCharacterMovement->GetMaxBrakingDeceleration());
		RelativeAcceleration = UKismetMathLibrary::Quat_UnrotateVector(
			OwningCharacter->GetTransform().GetRotation(), MaxClampedVelocityAccel/OwningCharacterMovement->GetMaxBrakingDeceleration());
	}
	return RelativeAcceleration;
	
}


