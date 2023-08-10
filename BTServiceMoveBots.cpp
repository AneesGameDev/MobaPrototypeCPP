// Fill out your copyright notice in the Description page of Project Settings.
#include "BTServiceMoveBots.h"
#include "MOBA_PrototypeGameModeBase.h"
#include "GruntsCPP.h"
#include "GruntsAIControllerCPP.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTServiceMoveBots::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Distance is Greater Than 500"));
	if (OwnerComp.GetAIOwner()) {

		AGruntsAIControllerCPP* AIController = Cast<AGruntsAIControllerCPP>(OwnerComp.GetAIOwner());

		AGruntsCPP* GruntsPawn = Cast<AGruntsCPP>(AIController->GetPawn());
		if (AIController && GruntsPawn) {

			//GruntsPawn->SetActorLocation(GruntsPawn->GetActorLocation() + 1.f);
			float Distance = FVector::Distance(GruntsPawn->GetActorLocation(), GruntsPawn->GruntPath.VectorArray[GruntsPawn->CurrentMovedIndex]);
			if (Distance < 250) {
				if (GruntsPawn->CurrentMovedIndex < GruntsPawn->GruntPath.VectorArray.Num() - 1) {
					AMOBA_PrototypeGameModeBase* GameModeBase = Cast<AMOBA_PrototypeGameModeBase>(GetWorld()->GetAuthGameMode());
					//GameModeBase->AIManager->
					//GameModeBase->AIManager = this;
					//GruntsPawn->MoveToNextTarget(OwnerComp.GetBlackboardComponent())
					FVector NexVectorValue;
					GruntsPawn->MoveToNextTarget(NexVectorValue);
					//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, TEXT("Next Vector Location Set"));
						//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("LOCATION: %f"), NexVectorValue.X));
					OwnerComp.GetBlackboardComponent()->SetValueAsVector("MoveToPath", NexVectorValue);
					//return EBTNodeResult::Succeeded;
				}
				else {
					//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Next Vector Location Is Not Set"));
					//return EBTNodeResult::Failed;
				}
			}
			else {
				//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Distance is Greater Than 100"));
				//return EBTNodeResult::Failed;
			}


		}

	}
}
