// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.h"
#include "Pickup.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	int RandomBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BonusHealing = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BonusHealth = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonuses)
	float BonusSpeed = 50.f;
	
	UFUNCTION()
	void Interact_Implementation(APlayerPawn* PlayerPawn);

	UFUNCTION()
	void HandleAnyPickup();

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PickupMesh;
};
