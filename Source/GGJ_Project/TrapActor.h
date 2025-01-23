// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactible.h"
#include "TrapActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GGJ_PROJECT_API ATrapActor : public AActor, public IInteractible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Interact_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TrapMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TrapActivationArea;

	UPROPERTY(EditAnywhere)
	float TravelUpDistance = 100;

	UPROPERTY(EditAnywhere)
	float TravelUpTimeSeconds = 0.5f;

	UPROPERTY(EditAnywhere)
	float ActivationCooldownSeconds = 2;

	UPROPERTY()
	FVector MeshUpperLocation; // upper position of a mesh

	UPROPERTY()
	FVector MeshLowerLocation; // upper position of a mesh

	UPROPERTY()
	float TravelUpSpeed = TravelUpDistance / TravelUpTimeSeconds;

	UPROPERTY()
	float TravelDownSpeed = -TravelUpDistance / ActivationCooldownSeconds;

	UPROPERTY()
	bool IsActivated = false;

	UPROPERTY()
	FTimerHandle ActivationTimerHandle;

	UFUNCTION()
	void ResetActivationState();
};
