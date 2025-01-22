// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGJ_Project/AI/BaseEnemyCharacter.h"
#include "MeleeAttackBot.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_PROJECT_API AMeleeAttackBot : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	AMeleeAttackBot();

	UFUNCTION()
	void MeeleAttack(AActor* Actor);

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle TimerHandle;
	
};
