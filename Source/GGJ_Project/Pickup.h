// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.h"
#include "Pickup.generated.h"

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
	void Interact_Implementation();

private:	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PickupMesh;
};
