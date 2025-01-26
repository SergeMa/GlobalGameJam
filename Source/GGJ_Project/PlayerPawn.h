// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BubblesGameMode.h"
#include "GameFramework/Character.h"
#include "PlayerPawn.generated.h"

class AProjectile;
class UPlayerAbilityComponent;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class GGJ_PROJECT_API APlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction* ActionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction* ActionLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction* ActionShoot;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	// Gunplay
	virtual void Shoot(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = Gunplay)
	virtual void OnTriggerPulled();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gunplay)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Abilities)
	UPlayerAbilityComponent* Abilities;

	UPROPERTY(EditAnywhere)
	int SpeedMultiplier = 1;
	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
	float CurrentHealth = 100;

	FTimerHandle BoostSpeedTimer;
	void BoostSpeed(float BoostTimer);
	void ResetSpeed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gunplay)
	UStaticMeshComponent* GunMeshComp;
	
	UFUNCTION()
	void AttachGun(bool bShouldBeInHand);

	UFUNCTION(BlueprintCallable)
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	float GetHealth();
private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
