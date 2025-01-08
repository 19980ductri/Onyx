// Fill out your copyright notice in the Description page of Project Settings.


#include "Onyx/Public/Characters/OnyxCharacterBase.h"


// Sets default values
AOnyxCharacterBase::AOnyxCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AOnyxCharacterBase::GetAbilitySystemComponent() const
{
	if (AbilitySystemComponent)
	{
		return AbilitySystemComponent;
	}
	return nullptr;
}
