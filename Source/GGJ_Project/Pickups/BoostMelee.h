// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BoostMelee.generated.h"

class APlayerPawn;

UCLASS()
class GGJ_PROJECT_API ABoostMelee : public APickup
{
	GENERATED_BODY()

public:
	ABoostMelee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* StaticMesh;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(APlayerPawn* PlayerPawn) override;

public:

	UFUNCTION()
	virtual void HandleAnyPickup();
};