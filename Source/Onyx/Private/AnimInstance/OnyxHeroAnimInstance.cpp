// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxHeroAnimInstance.h"

#include "Characters/OnyxPlayerCharacter.h"

void UOnyxHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AOnyxHeroCharacter>(OwningCharacter);
	}
}

void UOnyxHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	UpdateTrajectory(DeltaSeconds);
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

		UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(this, TrajectoryData, DeltaSeconds, Trajectory,
	PreviousDesiredControllerYaw,Trajectory,-1.f,30.f,0.1f,15.f);
}
