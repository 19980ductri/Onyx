// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OnyxPlayerState.generated.h"

class UOnyxAttributeSet;
class UOnyxAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ONYX_API AOnyxPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOnyxPlayerState();
	FORCEINLINE UOnyxAbilitySystemComponent* GetOnyxAbilitySystemComponent() const { return OnyxAbilitySystemComponent; }
	FORCEINLINE UOnyxAttributeSet* GetOnyxAttributes() const { return OnyxAttributeSet; }
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OnyxPlayerState", meta = (AllowPrivateAccess = "true"))
	UOnyxAbilitySystemComponent* OnyxAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OnyxPlayerState", meta = (AllowPrivateAccess = "true"))
	UOnyxAttributeSet* OnyxAttributeSet;
	
	
};
