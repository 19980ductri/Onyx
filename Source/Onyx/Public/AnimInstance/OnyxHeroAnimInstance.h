// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxCharacterAnimInstance.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "OnyxHeroAnimInstance.generated.h"

class AOnyxHeroCharacter;
/**
 * 
 */
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchTrajectoryData TrajectoryData_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	FPoseSearchTrajectoryData TrajectoryData_Moving;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float PreviousDesiredControllerYaw;
	
	
};
