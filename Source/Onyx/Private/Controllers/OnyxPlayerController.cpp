// Fill out your copyright notice in the Description page of Project Settings.


#include "Onyx/Public/Controllers/OnyxPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "OnyxGameplayTags.h"
#include "GameFramework/Character.h"
#include "Input/OnyxInputComponent.h"
#include "Input/OnyxInputConfig.h"

void AOnyxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(InputLocalPlayerSubsystem);

	InputLocalPlayerSubsystem->AddMappingContext(OnyxInputConfig->DefaultInputMappingContext, 0);

	UOnyxInputComponent* OnyxInputComponent = CastChecked<UOnyxInputComponent>(InputComponent);
	
	OnyxInputComponent->BindNativeAction(OnyxInputConfig, ETriggerEvent::Triggered, this, &ThisClass::Move, OnyxGameplayTag::InputTag_Move);
	OnyxInputComponent->BindNativeAction(OnyxInputConfig, ETriggerEvent::Triggered, this, &ThisClass::Look, OnyxGameplayTag::InputTag_Look);

}

void AOnyxPlayerController::Move(const FInputActionValue& InputActionValue)
{
	
	const FVector2d MovementVector = InputActionValue.Get<FVector2d>();
	const FRotator MovementRot(0, GetControlRotation().Yaw, 0);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRot.RotateVector(FVector::ForwardVector);
		GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRot.RotateVector(FVector::RightVector);
		GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
	}
	
}

void AOnyxPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2d& LookDirection = InputActionValue.Get<FVector2d>();
	
	if (LookDirection.X != 0.f)
	{
		AddYawInput(LookDirection.X);
	}
	if (LookDirection.Y != 0.f)
	{
		AddPitchInput(LookDirection.Y);
	}
}


