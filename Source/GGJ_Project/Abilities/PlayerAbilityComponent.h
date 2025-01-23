// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilityComponent.generated.h"

class URangedShot;
class UMeleeStomp;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API UPlayerAbilityComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPlayerAbilityComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	// Abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMeleeStomp* MeleeStomp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URangedShot* RangedShot;
};
