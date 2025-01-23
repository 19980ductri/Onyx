// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxHeroAnimInstance.h"

#include "Characters/OnyxPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



void UOnyxHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AOnyxHeroCharacter>(OwningCharacter);
	}
}

void UOnyxHeroAnimInstance::UpdateStates()
{
	LastFrameMovementMode = CurrentMovementMode;
	switch (OwningCharacterMovementComponent->MovementMode)
	{
	case MOVE_None:
	case MOVE_Walking:
	case MOVE_NavWalking:
		CurrentMovementMode = EAnimMovementMode::OnGround;
		break;
		
	case MOVE_Flying:
	case MOVE_Falling:
		CurrentMovementMode = EAnimMovementMode::InAir;
		break;
		
	case MOVE_Swimming:
	case MOVE_Custom:
		CurrentMovementMode = EAnimMovementMode::None;
		break;
		
	default:
		break;
	}

	LastFrameRotationMode = CurrentRotationMode;
	if (OwningCharacterMovementComponent->bOrientRotationToMovement == true)
	{
		CurrentRotationMode = ERotationMode::OrientationToMovement;
	}
	else
	{
		CurrentRotationMode = ERotationMode::Strafing;
	}
	
	LastFrameMovementState = CurrentMovementState;
	CurrentMovementState = IsMoving() ? EMovementState::Moving : EMovementState::Idle;
}

void UOnyxHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (OwningHeroCharacter == nullptr)
	{
		return;
	}
	UpdateTrajectory(DeltaSeconds);
	UpdateMotionMatchingEssentialValues(DeltaSeconds);
	UpdateStates();
}

void UOnyxHeroAnimInstance::UpdateTrajectory(float DeltaSeconds)
{
	FPoseSearchTrajectoryData TrajectoryData;
	
	if (GroundSpeed > 0.f)
	{
		TrajectoryData = TrajectoryData_Moving;
	}
	else
	{
		TrajectoryData = TrajectoryData_Idle;
	}
	UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(this, TrajectoryData,
		DeltaSeconds,Trajectory,
	PreviousDesiredControllerYaw,Trajectory,-1.f,
	30.f,0.1f,15.f);
	
	UPoseSearchTrajectoryLibrary::HandleTrajectoryWorldCollisions(OwningHeroCharacter, this,
		Trajectory, true, 0.01, Trajectory,
		TrajectoryCollision, TraceType, false, TArray<AActor*>(),
		EDrawDebugTrace::None, true);

	UPoseSearchTrajectoryLibrary::GetTrajectoryVelocity(Trajectory, -.3f, -.2f, TrajectoryPastVelocity, false);
	UPoseSearchTrajectoryLibrary::GetTrajectoryVelocity(Trajectory, 0.f, .2f, TrajectoryCurrentVelocity, false);
	UPoseSearchTrajectoryLibrary::GetTrajectoryVelocity(Trajectory, .4f, .5f, TrajectoryFutureVelocity, false);
}

float UOnyxHeroAnimInstance::GetTrajectoryTurnAngle()
{
	const FRotator FutureTrajectoryRotatorFromX = UKismetMathLibrary::MakeRotFromX(TrajectoryFutureVelocity);
	const FRotator VelocityRotatorFromX = UKismetMathLibrary::MakeRotFromX(Velocity);

	return UKismetMathLibrary::NormalizedDeltaRotator(FutureTrajectoryRotatorFromX, VelocityRotatorFromX).Yaw;
}

void UOnyxHeroAnimInstance::UpdateMotionMatchingEssentialValues(float DeltaSeconds)
{
	bIsMoving = IsMoving();
	bIsPivoting = IsPivoting();
	bIsStarting = IsStarting();
}

bool UOnyxHeroAnimInstance::IsPivoting()
{
	if (CurrentRotationMode == ERotationMode::OrientationToMovement)
	{
		PivotingAngleToCheck = 45.f;
	}
	else if (CurrentRotationMode == ERotationMode::Strafing)
	{
		PivotingAngleToCheck = 30.f;
	}

	bool bCanBePivoting = UKismetMathLibrary::Abs(GetTrajectoryTurnAngle()) >= PivotingAngleToCheck;
	
	if (IsMoving() && bCanBePivoting)
	{
		return true;
	}
	return false;
}

bool UOnyxHeroAnimInstance::IsStarting() const
{
	bool bHavingAttemptToMove = false;

	if (TrajectoryFutureVelocity.Size2D() >= Velocity.Size2D() + 100.f)
	{
		bHavingAttemptToMove = true;
	}
	
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Yellow, FString::Printf(TEXT("TrajectoryFutureVelocity: %f"), TrajectoryFutureVelocity.Size2D()));
	//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, FString::Printf(TEXT("Veloctity: %f"),  Velocity.Size2D() + 100.f));
	
	if (IsMoving() && bHavingAttemptToMove)
	{
		//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Yellow, FString::Printf(TEXT("is starting: true")));
		return true;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Yellow, FString::Printf(TEXT("is starting: false")));
		return false;	
	}
}

bool UOnyxHeroAnimInstance::IsMoving() const
{
	const bool HasVelocity = UKismetMathLibrary::NotEqual_VectorVector(Velocity, FVector::Zero(), 0.1);
	const bool bHasFutureTrajectoryVelocity = UKismetMathLibrary::NotEqual_VectorVector(TrajectoryFutureVelocity, FVector::Zero(), 10.f);
	const bool bHavingAccel = UKismetMathLibrary::NotEqual_VectorVector(Acceleration, FVector::Zero(), 0.f);
	if (HasVelocity && bHasFutureTrajectoryVelocity && bHasAcceleration)
	{
		return true;
	}
	return false;
}

bool UOnyxHeroAnimInstance::ShouldTurnInPlace() const
{
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(CharacterTransform.Rotator(), RootTransform.Rotator());
	float AbsoluteDeltaYaw = UKismetMathLibrary::Abs(DeltaRot.Yaw);

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("CharacterTransform.Rotator(): %s"), *CharacterTransform.Rotator().ToString()));
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Cyan, FString::Printf(TEXT("RootTransform.Rotator(): %s"), *RootTransform.Rotator().ToString()));
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Yellow, FString::Printf(TEXT("DeltaRot: %s"), *DeltaRot.ToString()));
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString::Printf(TEXT("AbsoluteDeltaYaw: %.2f"), AbsoluteDeltaYaw));
	}*/

	
	if (AbsoluteDeltaYaw >= 50.f)
	{
		return true;
	}
	return false;
}

