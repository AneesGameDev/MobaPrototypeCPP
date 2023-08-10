// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GruntsAIControllerCPP.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROTOTYPE_API AGruntsAIControllerCPP : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionComponent* sight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere)
	class AActor* NearestGrunt = nullptr;

	class AGruntsCPP* OwnerGrunt;

	FVector PreviousGruntLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPauseBehaviorTree;

	//UPROPERTY(EditDefaultsOnly, Category = "AI")
		//class FBlackboardKeySelector KSMoveToLoc;
	AGruntsAIControllerCPP();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);
	

	UFUNCTION()
		void StartBotAttack();

	UFUNCTION()
		void StartBotChasing();

	UFUNCTION()
		void SeePlayerByMovingOnLane();
};
