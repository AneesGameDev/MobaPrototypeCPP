// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityController.generated.h"




UCLASS()
class MOBA_PROTOTYPE_API AAbilityController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityController();
	UPROPERTY(EditAnywhere, Category = "PrimaryAbilities")
	TArray<TSubclassOf<AActor>> PrimaryAbilities;
	UPROPERTY(EditAnywhere, Category = "SecondaryAbilities")
	TArray<TSubclassOf<AActor>> SecondaryAbilities;

	FTimerHandle TimerDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CallPrimaryAbility(EPrimaryAbilities PAbilityOption, ACharacter* Character);

	void CallSecondaryAbility(ESecondaryAbilities PAbilityOption, ACharacter* Character);



};

UENUM(BlueprintType)
enum class EPrimaryAbilities : uint8
{
	Fire UMETA(DisplayName = "Fire"),
	Sword UMETA(DisplayName = "Sword")

};

UENUM(BlueprintType)
enum class ESecondaryAbilities : uint8
{
	PushEnemy UMETA(DisplayName = "PushEnemy"),
	MakeWall UMETA(DisplayName = "MakeWall"),
	MoveFast UMETA(DisplayName = "MoveFast"),
	FreezEnemy UMETA(DisplayName = "FreezEnemy"),
	StoneFire UMETA(DisplayName = "StoneFire")

};

