// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BoostHealth.generated.h"

class APlayerPawn;

UCLASS()
class GGJ_PROJECT_API ABoostHealth : public APickup
{
	GENERATED_BODY()

public:
	ABoostHealth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BonusHealing = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BonusHealth = 10.f;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(APlayerPawn* PlayerPawn) override;

public:
	UFUNCTION()
	virtual void HandleAnyPickup();
};
