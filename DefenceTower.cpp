// Fill out your copyright notice in the Description page of Project Settings.
#include "DefenceTower.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterCPP.h"
#include "GruntsCPP.h"
#include <GameFramework/Actor.h>
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BulletProjectileClass.h"
#include "SelfAttruibuteComponent.h"



// Sets default values
ADefenceTower::ADefenceTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*TowerBaseCylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderBaseOfTower"));
	TowerBaseCylinder->SetupAttachment(GetRootComponent());*/
	FireBeamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireBeamMesh"));
	//FireBeamMesh->SetupAttachment(GetRootComponent());
	PrimaryActorTick.bCanEverTick = true;

	sight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISneseConfig"));
	//AttachToPawn(GetPawn());

	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;

	// Add Sight Config to Perception Component
	sight->ConfigureSense(*SightConfig);
	sight->SetDominantSense(SightConfig->GetSenseImplementation());

}

// Called when the game starts or when spawned
void ADefenceTower::BeginPlay()
{
	Super::BeginPlay();
	FVector dummyVector(0.0f, 0.0f, 0.0f);
	dummyVector.X = MAX_FLT;   // set maximum dummy value for X
	dummyVector.Y = MAX_FLT;   // set maximum dummy value for Y
	dummyVector.Z = MAX_FLT;
	//PreviousTimeDelay = FPlatformTime::Seconds();


	SelfAttribute = Cast<USelfAttruibuteComponent>(this->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
	SelfAttribute->OwnerHealth = 1000;
	sight->OnPerceptionUpdated.AddDynamic(this, &ADefenceTower::OnPerceptionUpdate);
}

// Called every frame
void ADefenceTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DelayTime += DeltaTime;
	//PreviousTimeDelay = FPlatformTime::Seconds();
}

void ADefenceTower::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{


	for (auto Actors : UpdatedActors) {
		ITeamInterface* Interface = Cast<ITeamInterface>(Actors);


		ACharacter* DetectedChar = Cast<ACharacter>(Actors);
		AGruntsCPP* Grunt = Cast<AGruntsCPP>(Actors);

		if (Interface) {
			if (TowerID != Interface->GetTeamId()) {
				ActorsRef.Add(Actors);
				GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefenceTower::SpawnBulletsEverySeconds, DelayTime, true);
			}
		}
	


		//	APlayerCharacterCPP* Player = Cast<APlayerCharacterCPP>(Actors);
		//	if (Player)
		//	{
		//		if (TowerID != Player->PlayerID) {
		//			//Set Nearest Enemy and Start Attacking
		//			//return;
		//			//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
		//			//GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, GetActorLocation()-80.f, Rotation);
		//			//ActorRef  = Actors; 
		//			ActorsRef.Add(Actors);
		//			GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefenceTower::SpawnBulletsEverySeconds, DelayTime, true);
		//		}
		//		else {
		//			GetWorldTimerManager().ClearTimer(TimerHandle);
		//		}
		//	}
		//	else if (Grunt) 
		//	{
		//        if (TowerID != Grunt->GruntTeamId) {
		//
		//			//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Grunt->GetActorLocation());
		//			//GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, GetActorLocation() - 80.f, Rotation);
		//			//ActorRef  = Actors;
		//			ActorsRef.Add(Actors);
		//			GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefenceTower::SpawnBulletsEverySeconds, DelayTime, true);
		//		}
		//		else {
		//			GetWorldTimerManager().ClearTimer(TimerHandle);
		//		}
	 //       }

		//}

	}
}


void ADefenceTower::SpawnBulletsEverySeconds()
{
	ActorsRef.RemoveAll([&](const AActor* ref) 
		{return !IsValid(ref); });
	for(auto Actor : ActorsRef)
	{
		if (IsValid(Actor)) {
			FVector GlobalLoaction = FVector(GetActorLocation().X + VectorArray.X, GetActorLocation().Y + VectorArray.Y, GetActorLocation().Z + VectorArray.Z);
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GlobalLoaction, Actor->GetActorLocation());
			
			//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Defence Tower Perception Works 81, DefenceTower.cpp")));
			
				ABulletProjectileClass* Bullet = GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, GlobalLoaction, Rotation);
				if (Bullet) {
					Bullet->BulletSpawnerID = TowerID;
				}
				
		}
		else
		{

		}
	}
	//if (ActorsRef) {
	//	//CurrentTimeInSeconds = FPlatformTime::Seconds();
	//	//if (CurrentTimeInSeconds - PreviousTimeDelay > 2.f) {
	//		//PreviousTimeDelay = CurrentTimeInSeconds;
	//	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ActorRef->GetActorLocation());
	//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Defence Tower Perception Works 81, DefenceTower.cpp")));
	//		ABulletProjectileClass* Bullet = GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, GetActorLocation(), Rotation);
	//		//SpawnBulletsEverySeconds(Rotation);
	//	//}
	//

	//
	//}
}

void ADefenceTower::SetTeamId(int32 Id)
{
	TowerID = Id;
}

int32 ADefenceTower::GetTeamId()
{
	return TowerID;
}

void ADefenceTower::TakeDamage(float DamageAmount)
{
	/*ADefenceTower* Tower = Cast<ADefenceTower>(Actor);
	if (Tower) {*/
	if (SelfAttribute == nullptr) {
		SelfAttribute = Cast<USelfAttruibuteComponent>(SelfAttribute);
	}
	

		if (SelfAttribute && SelfAttribute->OwnerHealth > 11) {
			SelfAttribute->OwnerHealth -= DamageAmount;
				OnHealthUpdated.Broadcast(SelfAttribute->OwnerHealth);
		}
		else if (SelfAttribute)
		{
			//AGruntsAIControllerCPP* AIController = Cast<AGruntsAIControllerCPP>(GetController());
			//if (ensure(AIController)) {
				//AIController->NearestGrunt = nullptr;
			//}
			this->Destroy();
		}
	}
	


