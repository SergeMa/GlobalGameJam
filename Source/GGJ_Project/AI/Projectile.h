// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class GGJ_PROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	 UStaticMeshComponent *Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	 UProjectileMovementComponent* ProjectileMovement;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Niagara)
	 UNiagaraSystem* Niagara;

	 UFUNCTION()
	 virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		 const FHitResult& Hit);

	 virtual void SetInitialVelocity(FVector& LaunchVelocity);
};
