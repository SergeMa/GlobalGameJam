// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "RangedShot.generated.h"


class APlayerPawn;
class ABullet;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ_PROJECT_API URangedShot : public UAbility
{
	GENERATED_BODY()

public:
	URangedShot();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerPawn* Player;

public:
	virtual void UseAbility() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gunplay)
	bool bIsShooting;

	FTimerHandle ShotAnimTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gunplay)
	UAnimMontage* ShotMontage;
	
	UFUNCTION(BlueprintCallable, Category = Gunplay)
	void OnTriggerPulled();

	void OnShotEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gunplay)
	TSubclassOf<ABullet> BulletClass;
	
	void SpawnProjectile();
};
