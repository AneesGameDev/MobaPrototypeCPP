// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstanceCpp.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROTOTYPE_API UPlayerAnimInstanceCpp : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		APawn* Pawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsInAir;

	UFUNCTION(BlueprintCallable , Category= AnimationProperties)
	void UpDateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool bAttack =false;

	
	

	

	


};
