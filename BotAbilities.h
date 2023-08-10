// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BotAbilities.generated.h"

UCLASS()
class MOBA_PROTOTYPE_API ABotAbilities : public AActor
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere , Category = "DamageAmount")
	int32 DamageAmount;
	UPROPERTY(EditAnywhere , Category = "ParticleEffect")
	UParticleSystem* ParticeEffect;

	
public:	
	// Sets default values for this actor's properties
	ABotAbilities();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
