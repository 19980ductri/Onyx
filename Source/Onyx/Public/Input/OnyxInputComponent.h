// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "OnyxInputConfig.h"
#include "OnyxInputComponent.generated.h"


class UOnyxInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ONYX_API UOnyxInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserObject, typename CallbackFunc>
	void BindNativeAction(const UOnyxInputConfig* InputConfig, ETriggerEvent Event, UserObject* Object, CallbackFunc Callback, FGameplayTag InputTag);
	
	template<class  UserObject, typename PressedFunc, typename ReleasedFunc>
	void BindAbilityActions(const UOnyxInputConfig* InputConfig, UserObject* Object, PressedFunc PressedCallbackFunc, ReleasedFunc ReleasedCallbackFunc);
	
};

template <class UserObject, typename CallbackFunc>
void UOnyxInputComponent::BindNativeAction(const UOnyxInputConfig* InputConfig, ETriggerEvent Event, UserObject* Object,
	CallbackFunc Callback, FGameplayTag InputTag)
{
	check(InputConfig);
	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(FoundAction, Event, Object, Callback);
	}
}

template <class Class, typename PressedFunc, typename ReleasedFunc>
void UOnyxInputComponent::BindAbilityActions(const UOnyxInputConfig* InputConfig, Class* Object, PressedFunc PressedCallbackFunc,
	ReleasedFunc ReleasedCallbackFunc)
{
	check(InputConfig);

	for (const FOnyxInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.ActionTag.IsValid())
		{
			if (PressedCallbackFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedCallbackFunc, Action.ActionTag);
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedCallbackFunc, Action.ActionTag);
			}
		}
	}
}
