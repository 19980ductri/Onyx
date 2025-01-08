// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OnyxPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AOnyxPlayerCharacter::AOnyxPlayerCharacter()
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
