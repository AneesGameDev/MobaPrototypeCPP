// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNodeMoveBots.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBA_PROTOTYPE_API UBTTaskNodeMoveBots : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNodeMoveBots();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
