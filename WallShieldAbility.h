// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallShieldAbility.generated.h"

UCLASS()
class MOBA_PROTOTYPE_API AWallShieldAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallShieldAbility();


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> WallPrefab;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void ActivateWallAbility(ACharacter* Character);



};
