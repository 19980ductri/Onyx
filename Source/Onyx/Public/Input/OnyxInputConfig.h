// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "OnyxInputConfig.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct FOnyxInputAction
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ActionTag = FGameplayTag();
	
};


UCLASS()
class ONYX_API UOnyxInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<FOnyxInputAction> NativeInputActions;

	UPROPERTY(EditDefaultsOnly)
	TArray<FOnyxInputAction> AbilityInputActions	;

	
	UInputAction* FindNativeInputActionForTag(const FGameplayTag& Tag) const;
};
