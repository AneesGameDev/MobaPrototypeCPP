// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationsCpp/GruntsAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UGruntsAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
	}
}

void UGruntsAnimInstance::UpDateAnimationProperties()
{

	if (Pawn == nullptr) Pawn = TryGetPawnOwner();

	if (Pawn) {
		FVector VectorVelocity = Pawn->GetVelocity();

		FVector Velocity2D = FVector(VectorVelocity.X, VectorVelocity.Y, 0);

		Speed = 100.f;

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

	}

}
