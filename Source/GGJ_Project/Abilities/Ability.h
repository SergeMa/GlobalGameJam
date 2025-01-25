// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Ability.generated.h"


class APlayerPawn;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API UAbility : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UAbility();

	UPROPERTY()
	APlayerPawn* Player;
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	int Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float DamageInc = 10.f;
	
	virtual void UpgradeAbility();
	virtual void UseAbility();
};
