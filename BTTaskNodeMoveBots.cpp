// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTaskNodeMoveBots.h"
#include "MOBA_PrototypeGameModeBase.h"
#include "GruntsCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GruntsAIControllerCPP.h"



UBTTaskNodeMoveBots::UBTTaskNodeMoveBots()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskNodeMoveBots::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	AGruntsAIControllerCPP* AIController =Cast<AGruntsAIControllerCPP>(OwnerComp.GetAIOwner());

	AGruntsCPP* GruntsPawn =Cast<AGruntsCPP>(AIController->GetPawn());

	if (ensure(GruntsPawn)) {
		AMOBA_PrototypeGameModeBase* GameModeBase = Cast<AMOBA_PrototypeGameModeBase>(GetWorld()->GetAuthGameMode());
		//GameModeBase->AIManager->
		//GameModeBase->AIManager = this;
		//GruntsPawn->MoveToNextTarget(OwnerComp.GetBlackboardComponent())
		FVector NexVectorValue;
		GruntsPawn->MoveToNextTarget(NexVectorValue);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Next Vector Location Set"));

		OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToLoc", NexVectorValue);
		return EBTNodeResult::Succeeded;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Next Vector Location Is Not Set"));
		return EBTNodeResult::Failed;
	}

	
}
