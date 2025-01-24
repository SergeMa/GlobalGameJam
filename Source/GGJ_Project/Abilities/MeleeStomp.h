// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "MeleeStomp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API UMeleeStomp : public UAbility
{
	GENERATED_BODY()

public:
	UMeleeStomp();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Range = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float RangeInc = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Cooldown = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float CooldownInc = 5.f;

	FTimerHandle CooldownTimer;

protected:
	virtual void BeginPlay() override;

public:
	virtual void UseAbility() override;
	virtual void UpgradeAbility() override;
};
