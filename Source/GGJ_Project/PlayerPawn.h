// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerPawn.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	UInputAction* ActionMove;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value);
};
