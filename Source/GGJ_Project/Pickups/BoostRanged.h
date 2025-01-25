// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BoostRanged.generated.h"

UCLASS()
class GGJ_PROJECT_API ABoostRanged : public APickup
{
	GENERATED_BODY()

public:
	ABoostRanged();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* StaticMesh;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(APlayerPawn* PlayerPawn) override;

public:

	UFUNCTION()
	virtual void HandleAnyPickup();
};