// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstanceCpp.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstanceCpp::NativeInitializeAnimation()
{
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
	}
}

void UPlayerAnimInstanceCpp::UpDateAnimationProperties()
{

	if (Pawn == nullptr) Pawn = TryGetPawnOwner();

	if (Pawn) {
		FVector VectorVelocity = Pawn->GetVelocity();

		FVector Velocity2D = FVector(VectorVelocity.X, VectorVelocity.Y, 0);

		Speed = Velocity2D.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

	}

}
