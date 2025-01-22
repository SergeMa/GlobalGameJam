// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.h"
#include "Pickup.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GGJ_PROJECT_API APickup : public AActor, public IInteractible 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void Interact_Implementation();

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PickupMesh;
};
