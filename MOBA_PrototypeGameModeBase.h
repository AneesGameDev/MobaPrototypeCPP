// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AIManager.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MOBA_PrototypeGameModeBase.generated.h"



/**
 * 
 */
UCLASS()
class MOBA_PROTOTYPE_API AMOBA_PrototypeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIManager")
	AAIManager* AIManager;

	UPROPERTY(EditAnywhere, Category="BotAbilitiesBP")
	TArray<TSubclassOf<AActor>> BotAbilities;

		

		virtual void BeginPlay() override;

		UFUNCTION(BlueprintCallable)
		void SpawnBotsFromGameMode();
};
