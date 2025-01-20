// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnyxFunctionLibrary.generated.h"

class UOnyxAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ONYX_API UOnyxFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static bool DoesActorHaveTag(AActor* InActor, const FGameplayTag& InTag);
	static UOnyxAbilitySystemComponent* Native_GetAbilitySystemComponentFromActor(AActor* InActor);
};
