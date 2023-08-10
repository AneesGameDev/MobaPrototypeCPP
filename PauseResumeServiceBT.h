// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PauseResumeServiceBT.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBA_PROTOTYPE_API UPauseResumeServiceBT : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
