// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/OnyxInputConfig.h"

UInputAction* UOnyxInputConfig::FindNativeInputActionForTag(const FGameplayTag& Tag) const
{
	for (auto& Action: NativeInputActions)
	{
		if (Action.ActionTag.MatchesTagExact(Tag))
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
