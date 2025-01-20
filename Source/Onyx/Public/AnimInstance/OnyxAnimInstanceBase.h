// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "OnyxAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class ONYX_API UOnyxAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool DoesOwnerHaveTag(const FGameplayTag& Tag) const;
	
};
