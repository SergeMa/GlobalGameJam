// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGJ_Project/AI/Projectile.h"
#include "Bullet.generated.h"

UCLASS()
class GGJ_PROJECT_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	ABullet();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float Value);

	UFUNCTION()
	void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void SetInitialVelocity(FVector& LaunchVelocity);
};
