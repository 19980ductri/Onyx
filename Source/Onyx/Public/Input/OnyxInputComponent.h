// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "OnyxInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ONYX_API UOnyxInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class  Class, typename PressedFunc, typename ReleasedFunc>
	void BindAbilityActions(const)
	
};
