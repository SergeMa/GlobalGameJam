// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BubbleAIController.generated.h"

class UBehaviorTree;

UCLASS()
class GGJ_PROJECT_API ABubbleAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BT;

	virtual void OnPossess(APawn* InPawn) override;
	
};
