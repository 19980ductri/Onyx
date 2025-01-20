// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLib/OnyxFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/OnyxAbilitySystemComponent.h"

UOnyxAbilitySystemComponent* UOnyxFunctionLibrary::Native_GetAbilitySystemComponentFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UOnyxAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UOnyxFunctionLibrary::DoesActorHaveTag(AActor* InActor, const FGameplayTag& InTag)
{
	const UOnyxAbilitySystemComponent* ASC = Native_GetAbilitySystemComponentFromActor(InActor);
	return ASC->HasMatchingGameplayTag(InTag);	
}
