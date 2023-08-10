// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseResumeServiceBT.h"
#include "../GruntsCPP.h"
#include "../GruntsAIControllerCPP.h"
#include "BehaviorTree/BlackboardComponent.h"

void UPauseResumeServiceBT::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGruntsAIControllerCPP* GruntAIC = Cast<AGruntsAIControllerCPP>(OwnerComp.GetAIOwner());
		if(GruntAIC) {
			AGruntsCPP* GruntCPP = Cast<AGruntsCPP>(GruntAIC->GetPawn());
			if (GruntCPP) {
				GruntAIC->GetBlackboardComponent()->SetValueAsBool("PauseBehaviorTree", GruntCPP->IsPauseBT);
			}


	    }
}
