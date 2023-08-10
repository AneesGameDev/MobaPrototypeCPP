// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntsAIControllerCPP.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GruntsCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"Interface/TeamInterface.h"

AGruntsAIControllerCPP::AGruntsAIControllerCPP()
{

	sight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISneseConfig"));
	//AttachToPawn(GetPawn());

	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 600.0f;
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;

	// Add Sight Config to Perception Component
	sight->ConfigureSense(*SightConfig);
	sight->SetDominantSense(SightConfig->GetSenseImplementation());

}

void AGruntsAIControllerCPP::BeginPlay()
{
	Super::BeginPlay();
	
	//	
	RunBehaviorTree(BehaviorTree);



	
	FVector dummyVector(0.0f, 0.0f, 0.0f);
	dummyVector.X = MAX_FLT;   // set maximum dummy value for X
	dummyVector.Y = MAX_FLT;   // set maximum dummy value for Y
	dummyVector.Z = MAX_FLT;

	PreviousGruntLocation = dummyVector;


	//PerceptionComponent->ConfigureSense(*SightConfig);
	//APawn* GruntsPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	//if (GruntsPawn) {
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLoc", GruntsPawn->GetActorLocation());
	//	//GetBlackboardComponent()->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(this,0));
	//}

}

void AGruntsAIControllerCPP::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerGrunt = Cast<AGruntsCPP>(InPawn);
	sight->OnPerceptionUpdated.AddDynamic(this, &AGruntsAIControllerCPP::OnPerceptionUpdate);
}

void AGruntsAIControllerCPP::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("On Perception Update is Run >>")));
	//Super::OnPerceptionUpdate(UpdatedActors);
	//GetBlackboardComponent()->SetValueAsBool("PauseBehaviorTree", bPauseBehaviorTree);
	for (auto Actor : UpdatedActors)
	{
		//AGruntsCPP* DectectedGrunt = Cast<AGruntsCPP>(Actors);
		if (IsValid(Actor)) {

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Actor is Valid Linew 69 Controller")));
		ITeamInterface* Interface = Cast<ITeamInterface>(Actor);

		if (Interface && IsValid(OwnerGrunt)) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Interface and Owner Grunt ins Valid Line 73 Controller")));
			//&& (NearestGrunt == nullptr || (FVector::Distance(OwnerGrunt->GetActorLocation(), Actors->GetActorLocation())) < (FVector::Distance(OwnerGrunt->GetActorLocation(), NearestGrunt->GetActorLocation()) + 50.f))
			if (Interface->GetTeamId() != OwnerGrunt->GetTeamId() ) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Can See playe become Trun Line 76 Controller>>")));
			//if(GetBlackboardComponent()->HasKey)
				GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
				if (IsValid(OwnerGrunt) && IsValid(Actor)) {


						if (FVector::Distance(OwnerGrunt->GetActorLocation(), Actor->GetActorLocation()) < (PreviousGruntLocation.Size()+300.f)) {
							PreviousGruntLocation = Actor->GetActorLocation();
							NearestGrunt = Actor;
							GetBlackboardComponent()->SetValueAsObject("NearestEnemy", NearestGrunt);
							return;
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Nearest Grunt is Found >>")));
						}
			}
				
		}
		}


	}
	}
}

void AGruntsAIControllerCPP::StartBotAttack()
{

	GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
	GetBlackboardComponent()->SetValueAsBool("CanAttack", true);
	//NearestGrunt->Destroy();
}

void AGruntsAIControllerCPP::StartBotChasing()
{
	GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
	GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
	GetBlackboardComponent()->SetValueAsVector("MoveToLoc", NearestGrunt->GetActorLocation());
}

void AGruntsAIControllerCPP::SeePlayerByMovingOnLane()
{
	GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
	GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
}

//void AGruntsAIControllerCPP::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
//{
//
//}
