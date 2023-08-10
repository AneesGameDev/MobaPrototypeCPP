// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityController.h"
#include "Interface/TeamInterface.h"
#include "GameFramework/Character.h"
#include "PFireAbility.h"
#include "PushAbilityCpp.h"
#include "WallShieldAbility.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AAbilityController::AAbilityController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbilityController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbilityController::CallPrimaryAbility(EPrimaryAbilities PAbilityOption, ACharacter* Character)
{
	ITeamInterface* TeamInterface = Cast<ITeamInterface>(Character);

	if (TeamInterface) {
		APFireAbility* PFireAbilityObj;
		//APushAbilityCpp* PushAbility;
		
		switch (PAbilityOption)
		{
		case EPrimaryAbilities::Fire:

			PFireAbilityObj = GetWorld()->SpawnActor<APFireAbility>(PrimaryAbilities[(int)EPrimaryAbilities::Fire]);
			if (PFireAbilityObj) {
				PFireAbilityObj->ActivatePFireAbility(Character);
			}
			else
			{

			}
			break;
		case EPrimaryAbilities::Sword:

			PFireAbilityObj = GetWorld()->SpawnActor<APFireAbility>(PrimaryAbilities[(int)EPrimaryAbilities::Sword]);
			if (PFireAbilityObj) {
				PFireAbilityObj->ActivatePFireAbility(Character);
			}
			else
			{

			}

			break;
		default:
			break;
		}
	}

}

void AAbilityController::CallSecondaryAbility(ESecondaryAbilities PAbilityOption, ACharacter* Character)
{
	APushAbilityCpp* PushAbilityActor;
	AWallShieldAbility* WallAbilityActor;
	APFireAbility* StoneFireAbility;

	switch (PAbilityOption)
	{
	case ESecondaryAbilities::PushEnemy:
		PushAbilityActor = GetWorld()->SpawnActor<APushAbilityCpp>(SecondaryAbilities[(int)ESecondaryAbilities::PushEnemy]);
		if (PushAbilityActor) {
			PushAbilityActor->ActivatePushAbility();
		}

		break;
	case ESecondaryAbilities::MakeWall:

		WallAbilityActor = GetWorld()->SpawnActor<AWallShieldAbility>(SecondaryAbilities[(int)ESecondaryAbilities::MakeWall]);
		if (WallAbilityActor) {
			WallAbilityActor->ActivateWallAbility(Character);
		}


		break;
	case ESecondaryAbilities::MoveFast:
	
	{
		UCharacterMovementComponent* MovementComponent;
		MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent) {
			MovementComponent->MaxWalkSpeed = 20000.f;
			//MovementComponent->MaxAcceleration = 5000.f;
			//MovementComponent->BrakingFriction = 3000.f;



			FTimerDelegate Delegatee;
			Delegatee.BindLambda([MovementComponent] {
				MovementComponent->MaxWalkSpeed = 1000.f;
			MovementComponent->MaxAcceleration = 2400.f;
			MovementComponent->BrakingFriction = 0.f;
				});
			GetWorldTimerManager().SetTimer(TimerDelay, Delegatee, 5.f, false);

		}

		

	}
		break;
	case ESecondaryAbilities::FreezEnemy:
		break;

	case ESecondaryAbilities::StoneFire:

		StoneFireAbility = GetWorld()->SpawnActor<APFireAbility>(SecondaryAbilities[(int)ESecondaryAbilities::StoneFire]);
		if (StoneFireAbility) {
			StoneFireAbility->ActivatePFireAbility(Character);
		}


		break;
	default:
		break;
	}
}

