// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Ability.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API UAbility : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UAbility();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	int Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float DamageInc = 1.5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Range = 200;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float RangeInc = 1.1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Cooldown = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float CooldownInc = 0.9;

	FTimerHandle CooldownTimer;
	
	virtual void UpgradeAbility();
	virtual void UseAbility();
};
