// Fill out your copyright notice in the Description page of Project Settings.


#include "PushAbilityCpp.h"
#include "Kismet/GameplayStatics.h"
#include "../BulletProjectileClass.h"
#include "GameFramework/Character.h"
#include "Interface/TeamInterface.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APushAbilityCpp::APushAbilityCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APushAbilityCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushAbilityCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushAbilityCpp::ActivatePushAbility()
{

	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->GetPlayerViewPoint(Location, Rotation);


	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);
	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);

	FVector EndLocation = Rotation.Vector() * 1500;
	EndLocation += Location;

	//const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	ECollisionChannel TraceChannel;
	TraceChannel = ECollisionChannel::ECC_Pawn;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 

	bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel, Params);
	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel);

	if (LineTrace) {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LineTraceInnerFunction Is Called"));
		DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, 10.f);

		AActor* Actor = HitResult.GetActor();
		ITeamInterface* Interface = Cast<ITeamInterface>(Actor);
		//&& Interface->GetTeamId() != this->GetTeamId()
		if (Interface) {
			//GetComponentByClass(Actor)
			//Actor->AddIm(HitResult.Normal * -100000);
			ACharacter* Character = Cast<ACharacter>(Actor);
			if (Character) {
				FVector HitNormal = HitResult.Normal; // Assuming you have a HitResult object from the hit event
				FVector OppositeDirection = -1 * HitNormal;
				//Character->GetCapsuleComponent()->SetSimulatePhysics(true);
				//bPushForceCount = 100;
				
				Character->GetCapsuleComponent()->SetSimulatePhysics(true);
				Character->GetCapsuleComponent()->AddImpulse(HitResult.Normal * -100000);
				FTimerDelegate Delegate;
				Delegate.BindLambda([Character] {Character->GetCapsuleComponent()->SetSimulatePhysics(false);
				//Character->SetActorLocation(Character->GetActorLocation());
				//bPushForce = false;
					});
				GetWorldTimerManager().SetTimer(TimerDelay, Delegate, 3.f, false);



			}
		}
	}
}
