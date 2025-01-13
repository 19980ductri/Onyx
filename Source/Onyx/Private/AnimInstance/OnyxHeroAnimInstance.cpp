// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/OnyxHeroAnimInstance.h"

#include "Characters/OnyxPlayerCharacter.h"

void UOnyxHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AOnyxHeroCharacter>(OwningCharacter);
	}
}

void UOnyxHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
