// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTFindCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_PROJECT_API UBTTFindCharacter : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTFindCharacter();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
