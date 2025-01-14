// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxCharacterAnimInstance.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "OnyxHeroAnimInstance.generated.h"

class AOnyxHeroCharacter;





UCLASS()
class ONYX_API UOnyxHeroAnimInstance : public UOnyxCharacterAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|References", meta = (AllowPrivateAccess = "true"))
	AOnyxHeroCharacter* OwningHeroCharacter;

	void UpdateTrajectory(float DeltaSeconds);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchQueryTrajectory Trajectory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchTrajectory_WorldCollisionResults TrajectoryCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector TrajectoryPastVelocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector TrajectoryCurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FVector TrajectoryFutureVelocity;

	float GetTrajectoryTurnAngle();
	
	void UpdateMotionMatchingEssentialValues(float DeltaSeconds);

	
	UFUNCTION(BlueprintPure, Category = "AnimData|LocomotionData", meta= (BlueprintThreadSafe = "true"))
	bool IsPivoting();
	
	UFUNCTION(BlueprintPure, Category = "AnimData|LocomotionData", meta= (BlueprintThreadSafe = "true"))
	bool IsStarting();

	UFUNCTION(BlueprintPure, Category = "AnimData|LocomotionData", meta= (BlueprintThreadSafe = "true"))
	bool IsMoving();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bIsPivoting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bIsStarting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bIsMoving;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	TEnumAsByte<ETraceTypeQuery> TraceType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchTrajectoryData TrajectoryData_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchTrajectoryData TrajectoryData_Moving;


	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float PreviousDesiredControllerYaw;
	


	
};
