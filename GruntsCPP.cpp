// Fill out your copyright notice in the Description page of Project Settings.
#include "GruntsCPP.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "BotAbilities.h"
#include "Components/BoxComponent.h"
#include "SelfAttruibuteComponent.h"
#include "GruntsAIControllerCPP.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Interface/TeamInterface.h"
#include "net/UnrealNetwork.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AGruntsCPP::AGruntsCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));

	BoxComponent->SetupAttachment(GetMesh(), "StartLocation_Attack");
	
	//BoxComponent->SetBoxExtent(FVector(3.f, 0.745f, 0.8f));
	//BoxComponent->SetRelativeScale3D(FVector(83.f, 49.f, -33.f));

	//AttackParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Attack Particle"));

}

void AGruntsCPP::OnRep_TeamID()
{
	USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(this->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
	if (SelfComponent) {
		SelfComponent->OwnerHealth = 100.f;
	}
	GetMesh()->SetSkeletalMesh(GruntTeamId == 1 ? GruntSkeletalA : GruntSkeletalB);
}

void AGruntsCPP::Atteck_Anim_Play_Implementation()
{

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (Atteck)
		{
			AnimInstance->Montage_Play(Atteck);
			//if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("play montage Ai"));
		}

	}


}

void AGruntsCPP::MoveToNextTarget(FVector& OutLocation)
{
	if (CurrentMovedIndex < GruntPath.VectorArray.Num()-1) {
		CurrentMovedIndex += 1;
		OutLocation = GruntPath.VectorArray[CurrentMovedIndex];
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Current Index Length : %d"),CurrentMovedIndex));
	}
}



// Called when the game starts or when spawned
void AGruntsCPP::BeginPlay()
{
	Super::BeginPlay();
	CurrentMovedIndex = 0;
	
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGruntsCPP::OverlapBegin);
	//GetMesh()->SetSkeletalMesh
//	HelathBaarWidget = CreateWidget<UUserWidget>(this, HealthWidget);
//	if (HelathBaarWidget != nullptr) {
//		HelathBaarWidget->AddToViewport();
//}
	OnHealthUpdated.Broadcast(100.f);
}

// Called every frame
void AGruntsCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGruntsCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGruntsCPP::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ITeamInterface* Interface = Cast<ITeamInterface>(OtherActor);
	if (Interface) {
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Outer Overlap Begin Called , GruntCPP")));
		if (Interface->GetTeamId() != this->GruntTeamId) {
			//BotAbiliyTemp = Cast<ABotAbilities>(BotAbility.GetDefaultObject());

			if (ParticeEffectt) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticeEffectt, OtherActor->GetActorLocation());
				//GiveDamage(EnemyGrunt, Cast<ABotAbilities>(EnemyGrunt->BotAbility->GetDefaultObject())->DamageAmount);
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("On Overlap Begin is Worked line 71 , GruntCPP")));
				//TakeDamage(OtherActor, 5.f);
				USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(OtherActor->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
				if (SelfComponent) {
					if (SelfComponent->OwnerHealth < 15) {
						AGruntsAIControllerCPP* AIController = Cast<AGruntsAIControllerCPP>(GetController());
						if (AIController) {
							AIController->NearestGrunt = nullptr;
							//AIController->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
						}
					}
				}
				Interface->TakeDamage(10.f);
			}
			
		}
	}
	//if (AGruntsCPP* EnemyGrunt = Cast<AGruntsCPP>(OtherActor)) {
	//	if(EnemyGrunt->GruntTeamId != this->GruntTeamId){
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ABotAbilities>(BotAbility->GetDefaultObject())->ParticeEffect, EnemyGrunt->GetActorLocation());
	//	GiveDamage(EnemyGrunt, Cast<ABotAbilities>(EnemyGrunt->BotAbility->GetDefaultObject())->DamageAmount);
	//	}
	//}

}

void AGruntsCPP::AttackLineTrace()
{
	/*
	FVector StartLocation = GetMesh()->GetSocketLocation("StartLocation_Attack");
	FVector EndLocation = GetMesh()->GetSocketLocation("EndLocation_Attack");
	// Get the player controller
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Attack Line Trace Called")));
	
	// Get the camera location and forward vector
	if (!StartBool)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Start Bool is  :: False ")));
		ParticeIsPlaying = false;
		GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	}

	

	FHitResult HitResult;

	FCollisionObjectQueryParams CC;
	CC.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FCollisionQueryParams TraceParams; 
	TraceParams.AddIgnoredActor(this);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2.f);
	//Perform the line trace against the object//, FCollisionQueryParams()
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, CC, TraceParams))
	{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Attack Trace Run")));
	//	// Handle the hit result
		if (auto HitActor = HitResult.GetActor()) {

			if (auto EnemyHitGrunt = Cast<AGruntsCPP>(HitActor)) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Attack Trace Run")));
				//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplodeGrenadeParticals,Location);

				if (!ParticeIsPlaying) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ABotAbilities>(BotAbility->GetDefaultObject())->ParticeEffect, HitResult.Location);
				//GiveDamage(EnemyHitGrunt , Cast<ABotAbilities>(EnemyHitGrunt->BotAbility->GetDefaultObject())->DamageAmount);
				ParticeIsPlaying = true;
				// The line trace hit the object
			}
		}
	}
	
	*/


}

void AGruntsCPP::AttackLineTraceTime()
{
	//if (StartBool) {
		//GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AGruntsCPP::AttackLineTrace, 0.2f, true);
	//}

	
}

void AGruntsCPP::GiveDamage(AGruntsCPP* Grunt,float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Give Damage is Called"));
	USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(Grunt->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
	

	



}

void AGruntsCPP::SetTeamId(int32 Id)
{
	GruntTeamId = Id;
}

int32 AGruntsCPP::GetTeamId()
{
	return GruntTeamId;
}

void AGruntsCPP::TakeDamage(float DamageAmount)
{
	//AActor* Grunt = Cast<AActor>(Actor);
	//if (Grunt) {
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Damage Called on Line 177 , GruntCPP")));
		USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GetComponentByClass(USelfAttruibuteComponent::StaticClass()));

		if (SelfComponent && SelfComponent->OwnerHealth > 11) {
			SelfComponent->OwnerHealth -= DamageAmount;
			OnHealthUpdated.Broadcast(SelfComponent->OwnerHealth);
		}
		else if (SelfComponent)
		{
			AGruntsAIControllerCPP* AIController = Cast<AGruntsAIControllerCPP>(GetController());
			if (ensure(AIController)) {
				AIController->NearestGrunt = nullptr;
				//AIController->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
			}

			DestroyActorOnServer();
		}

}

void AGruntsCPP::DestroyActorOnServer_Implementation() {
	this->Destroy(true);
}


//void AGruntsCPP::TakeDamageMulticast(float DamageAmount)
//{
//}

void AGruntsCPP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AGruntsCPP, GruntTeamId, COND_None, REPNOTIFY_Always);
}


