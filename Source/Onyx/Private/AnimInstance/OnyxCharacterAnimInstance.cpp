// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxCharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Characters/OnyxCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	
}
