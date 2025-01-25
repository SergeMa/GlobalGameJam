// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ_Project/Interactible.h"
#include "Pickup.generated.h"

class APlayerPawn;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupEvent);

UCLASS()
class GGJ_PROJECT_API APickup : public AActor, public IInteractible 
{
	GENERATED_BODY()
	
public:
	APickup();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	virtual void Interact_Implementation(APlayerPawn* PlayerPawn);

	UPROPERTY()
	bool bShouldGoUp = true;
	
	UFUNCTION()
	virtual void Tick(float DeltaTime) override;
};
