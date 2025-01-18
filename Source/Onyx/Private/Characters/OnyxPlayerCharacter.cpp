// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OnyxPlayerCharacter.h"

#include "AbilitySystem/OnyxAbilitySystemComponent.h"
#include "AbilitySystem/OnyxAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/OnyxPlayerState.h"


// Sets default values
AOnyxHeroCharacter::AOnyxHeroCharacter()
{
	//of the root mesh
	MeshComponentName = FName("Root Mesh Component");

	//auto retarget from the root mesh through ABP_GenericRetarget
	MainCharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainCharacterMesh");
	MainCharacterMesh->SetupAttachment(GetMesh());
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
}

void AOnyxHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityInfo();
	
}

void AOnyxHeroCharacter::InitAbilityInfo()
{
	AOnyxPlayerState* OnyxPlayerState = GetPlayerState<AOnyxPlayerState>();

	check(OnyxPlayerState);
	
	OnyxPlayerState->GetOnyxAbilitySystemComponent()->InitAbilityActorInfo(OnyxPlayerState, this);
	
	SetAbilitySystemComponent(OnyxPlayerState->GetOnyxAbilitySystemComponent());
	SetAttributeSet(OnyxPlayerState->GetOnyxAttributeSet());

	check(GetAbilitySystemComponent());
	check(GetAttributeSet());
	
}

void AOnyxHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOnyxHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityInfo();
}
