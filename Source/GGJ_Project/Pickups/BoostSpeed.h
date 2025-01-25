// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BoostSpeed.generated.h"

UCLASS()
class GGJ_PROJECT_API ABoostSpeed : public APickup
{
	GENERATED_BODY()

public:
	ABoostSpeed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BoostTimer = 10.f;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(APlayerPawn* PlayerPawn) override;

public:
	UFUNCTION()
	virtual void HandleAnyPickup();
};