// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AttackInfoBTService.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBA_PROTOTYPE_API UAttackInfoBTService : public UBTService
{
	GENERATED_BODY()
		
		UPROPERTY()
	class AActor* Grunt;
	UPROPERTY()
	class AActor* EnemyGrunt;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
