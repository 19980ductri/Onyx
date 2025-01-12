// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "OnyxPlayerController.generated.h"

class UOnyxInputConfig;
/**
 * 
 */
UCLASS()
class ONYX_API AOnyxPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UOnyxInputConfig> OnyxInputConfig;

	
	
protected:
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
};
