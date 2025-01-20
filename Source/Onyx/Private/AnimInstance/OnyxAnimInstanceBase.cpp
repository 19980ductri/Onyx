// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxAnimInstanceBase.h"

#include "FunctionLib/OnyxFunctionLibrary.h"

bool UOnyxAnimInstanceBase::DoesOwnerHaveTag(const FGameplayTag& Tag) const
{
	if (APawn* OwningPawn =	TryGetPawnOwner())
	{
		return	UOnyxFunctionLibrary::DoesActorHaveTag(OwningPawn, Tag);
	}
	return false;
}
