// Fill out your copyright notice in the Description page of Project Settings.

//#include "BulletProjectileClass.h"
#include "PFireAbility.h"
#include "Kismet/GameplayStatics.h"
#include "../BulletProjectileClass.h"
#include "GameFramework/Character.h"
#include "Interface/TeamInterface.h"


// Sets default values
APFireAbility::APFireAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APFireAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFireAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APFireAbility::ActivatePFireAbility(ACharacter* OwnerCharacter)
{



	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("ShootingLineTrace is Called")));
	FVector Location;
	FRotator Rotation;
	FRotator SpawnRotation;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->GetPlayerViewPoint(Location, Rotation);
	//Rotation.Vector()+FVector(0.f,-185.f,0.f);
	FRotator RotationOffset = FRotator(0.f, 5.f, 0.f); // Set the rotation offset to (0, 45, 0)
	Rotation += RotationOffset;

	ABulletProjectileClass* BulletProjectile;

	BulletProjectile = Cast<ABulletProjectileClass>(GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, OwnerCharacter->GetMesh()->GetSocketLocation("ShootingLocation"), Rotation));


	ITeamInterface* TeamInterface = Cast<ITeamInterface>(OwnerCharacter);

	if (TeamInterface && BulletProjectile) {

			BulletProjectile->BulletSpawnerID = TeamInterface->GetTeamId();
	
	}
}
