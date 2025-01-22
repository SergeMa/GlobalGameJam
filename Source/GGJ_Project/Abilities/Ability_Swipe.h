// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Components/PrimitiveComponent.h"
#include "Ability_Swipe.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API UAbility_Swipe : public UPrimitiveComponent, public IAbility
{
	GENERATED_BODY()

public:
	UAbility_Swipe();

protected:
	virtual void BeginPlay() override;

public:
	virtual void AcquireAbility_Implementation() override;
	virtual void UpgradeAbility_Implementation() override;
	virtual void UseAbility_Implementation() override;
};
