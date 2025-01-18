﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnyxCharacterBase.h"
#include "OnyxPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ONYX_API AOnyxHeroCharacter : public AOnyxCharacterBase
{
	GENERATED_BODY()

public:
	AOnyxHeroCharacter();

	
protected:

	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilityInfo() override;

	virtual void BeginPlay() override;
	
	
private:

	virtual void OnRep_PlayerState() override;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MainCharacterMesh;
	
};
