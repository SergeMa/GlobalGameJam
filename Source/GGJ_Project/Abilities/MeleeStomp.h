﻿// Fill out your copyright notice in the Description page of Project Settings.

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

protected:
	virtual void BeginPlay() override;

public:
	virtual void UseAbility() override;
};
