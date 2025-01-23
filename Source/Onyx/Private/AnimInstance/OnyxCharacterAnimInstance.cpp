// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxCharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Characters/OnyxCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimationWarpingLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UOnyxCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AOnyxCharacterBase>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningCharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
	
}

void UOnyxCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!OwningCharacter || !OwningCharacterMovementComponent)
	{
		return;
	}

	LastFrameCharacterTransform = CharacterTransform;
	CharacterTransform = OwningCharacter->GetActorTransform();

	
	const FTransform OffsetRootTrans = UAnimationWarpingLibrary::GetOffsetRootTransform(OffsetNode);
	const FRotator OffsetRootRotation =  FRotator(OffsetRootTrans.Rotator().Roll, OffsetRootTrans.Rotator().Pitch, OffsetRootTrans.Rotator().Yaw + 90.f);
	RootTransform = UKismetMathLibrary::MakeTransform(OffsetRootTrans.GetLocation(), OffsetRootRotation);
	
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	CurrentRotationMode = ERotationMode::OrientationToMovement;
	AccelerationLastFrame = Acceleration;
	Acceleration = OwningCharacterMovementComponent->GetCurrentAcceleration();

	
	
	VelocityLastFrame = Velocity;
	Velocity = OwningCharacterMovementComponent->Velocity;
	VelocityAcceleration = (Velocity - VelocityLastFrame) / UKismetMathLibrary::FMax(DeltaSeconds, 0.001f);
	
	
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	
}

void UOnyxCharacterAnimInstance::UpdateStates()
{
	
}

FVector UOnyxCharacterAnimInstance::CalculateRelativeAccelerationAmount() const
{
	if (OwningCharacterMovementComponent == nullptr || OwningCharacter == nullptr)
	{
		return FVector(0, 0, 0);
	}
	
	FVector RelativeAcceleration;
	
	if (OwningCharacterMovementComponent->MaxAcceleration < 0 && OwningCharacterMovementComponent->GetMaxBrakingDeceleration() < 0 ||
		CurrentMovementMode == EAnimMovementMode::InAir)
	{
		return FVector(0, 0, 0);
	}
	
	const float DotValue = UKismetMathLibrary::Dot_VectorVector(Acceleration, Velocity);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("DotValue: %f"), DotValue));
	if (DotValue > 0)
	{
		const FVector MaxClampedVelocityAccel = UKismetMathLibrary::Vector_ClampSizeMax(VelocityAcceleration,OwningCharacterMovementComponent->MaxAcceleration);
		RelativeAcceleration = UKismetMathLibrary::Quat_UnrotateVector(
			OwningCharacter->GetTransform().GetRotation(), MaxClampedVelocityAccel/OwningCharacterMovementComponent->MaxAcceleration);
	
	}
	else
	{
		const FVector MaxClampedVelocityAccel = UKismetMathLibrary::Vector_ClampSizeMax(VelocityAcceleration,OwningCharacterMovementComponent->GetMaxBrakingDeceleration());
		RelativeAcceleration = UKismetMathLibrary::Quat_UnrotateVector(
			OwningCharacter->GetTransform().GetRotation(), MaxClampedVelocityAccel/OwningCharacterMovementComponent->GetMaxBrakingDeceleration());
	}
	return RelativeAcceleration;
}


