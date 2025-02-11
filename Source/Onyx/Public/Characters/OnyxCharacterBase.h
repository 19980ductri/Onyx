// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "OnyxCharacterBase.generated.h"

UCLASS(Abstract)
class ONYX_API AOnyxCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOnyxCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
private:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
