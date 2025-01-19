// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "OnyxAbilityDataSet.generated.h"


class UGameplayAbility;

USTRUCT(BlueprintType)
struct FOnyxAbilityInfo
{
	GENERATED_BODY()

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	FGameplayTag AbilityTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	FGameplayTag CooldownTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	FGameplayTag StatusTag = FGameplayTag();
/*
 * below to be added more if needed
 */
};


UCLASS(Blueprintable, BlueprintType)
class ONYX_API UOnyxAbilityDataSet : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OnyxAbilityDataSet")
	TArray<FOnyxAbilityInfo> AbilityInfos;

	FOnyxAbilityInfo FindAbilityInfoByTag(const FGameplayTag& AbilityTag);
	
};
