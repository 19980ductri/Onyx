// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OnyxPlayerState.h"

#include "AbilitySystem/OnyxAbilitySystemComponent.h"
#include "AbilitySystem/OnyxAttributeSet.h"

AOnyxPlayerState::AOnyxPlayerState()
{
	OnyxAbilitySystemComponent = CreateDefaultSubobject<UOnyxAbilitySystemComponent>(FName("Onyx Ability System Component"));
	OnyxAbilitySystemComponent->SetIsReplicated(true);
	
	OnyxAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	OnyxAttributeSet = CreateDefaultSubobject<UOnyxAttributeSet>(FName("Onyx Attribute Set"));

	SetNetUpdateFrequency(100.f);
}
