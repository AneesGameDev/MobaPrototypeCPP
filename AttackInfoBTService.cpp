// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackInfoBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GruntsAIControllerCPP.h"
#include "GruntsCPP.h"

void UAttackInfoBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGruntsAIControllerCPP* GruntsAIC = Cast<AGruntsAIControllerCPP>(OwnerComp.GetAIOwner());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Nearest Enemy is Found in Service")));

	if (GruntsAIC) {
		 Grunt = Cast<AGruntsCPP>(GruntsAIC->GetPawn());
	}

	if (Cast<AActor>(GruntsAIC->GetBlackboardComponent()->GetValueAsObject("NearestEnemy"))) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Nearest Enemy is Foundin Service")));
		EnemyGrunt = Cast<AActor>(GruntsAIC->GetBlackboardComponent()->GetValueAsObject("NearestEnemy"));
		if ((FVector::Distance(Grunt->GetActorLocation(), EnemyGrunt->GetActorLocation()) < 150)) {
			GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
			GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanAttack", true);
			GruntsAIC->GetBlackboardComponent()->SetValueAsVector("MoveToLoc", EnemyGrunt->GetActorLocation());
			//GruntsAIC->GetBlackboardComponent()->SetValueAsObject("NearestEnemy", EnemyGrunt);
		}
		else
		{
			GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
			GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
			GruntsAIC->GetBlackboardComponent()->SetValueAsVector("MoveToLoc", EnemyGrunt->GetActorLocation());
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Nearest Enemy is Not Foundin Service")));
		GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
		GruntsAIC->GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
	}

}
