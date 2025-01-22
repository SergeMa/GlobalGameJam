// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GGJ_PROJECT_API IAbility
{
	GENERATED_BODY()

public:
	int Level = 0;
	float Damage = 0;
	float Range = 0;
	float Cooldown = 0.f;

	FTimerHandle CooldownTimer;
	
	UFUNCTION(BlueprintNativeEvent)
	void AcquireAbility();
	UFUNCTION(BlueprintNativeEvent)
	void UpgradeAbility();
	UFUNCTION(BlueprintNativeEvent)
	void UseAbility();
};
