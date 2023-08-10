// Fill out your copyright notice in the Description page of Project Settings.


#include "WallShieldAbility.h"
#include "Kismet/GameplayStatics.h"
#include "../BulletProjectileClass.h"
#include "GameFramework/Character.h"
#include "Interface/TeamInterface.h"
#include "Components/CapsuleComponent.h"
#include "AbilityActor.h"


// Sets default values
AWallShieldAbility::AWallShieldAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallShieldAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallShieldAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallShieldAbility::ActivateWallAbility(ACharacter* Character)
{


	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->GetPlayerViewPoint(Location, Rotation);


	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);
	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);

	FVector EndLocation = Rotation.Vector() * 500;
	EndLocation += Location;

	//const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	ECollisionChannel TraceChannel;
	TraceChannel = ECollisionChannel::ECC_Pawn;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);
	// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 
	ITeamInterface* OwnerInterface;

	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel, Params);
	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel);

//	if (LineTrace) {


		//AActor* Actor = HitResult.GetActor();
		//ITeamInterface* Interface = Cast<ITeamInterface>(Actor);
		 OwnerInterface = Cast<ITeamInterface>(Character);

		

			UWorld* World = GetWorld(); // Get a reference to the world
			if (World)
			{
				FVector SpawnLocation = Character->GetActorLocation() + (Character->GetActorForwardVector() * 500.f); // Calculate the spawn location in front of the actor
				FRotator SpawnRotation = Character->GetActorRotation(); // Use the actor's rotation
				AAbilityActor* WallAbility = World->SpawnActor<AAbilityActor>(WallPrefab, SpawnLocation, SpawnRotation); // Spawn the cube actor at the calculated location
				//CubeActor->SetOwner(this);
				WallAbility->SpawnerID = OwnerInterface->GetTeamId();
			}
	
		//else
		//{
		//UWorld* World = GetWorld(); // Get a reference to the world
		//if (World)
		//{
		//	FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 500.f); // Calculate the spawn location in front of the actor
		//	FRotator SpawnRotation = GetActorRotation(); // Use the actor's rotation
		//	AAbilityActor* WallAbility = World->SpawnActor<AAbilityActor>(WallPrefab, SpawnLocation, SpawnRotation); // Spawn the cube actor at the calculated location
		//	WallAbility->SpawnerID = OwnerInterface->GetTeamId();
		//}
	
		//}
	}





