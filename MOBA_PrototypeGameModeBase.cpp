// Copyright Epic Games, Inc. All Rights Reserved.


#include "MOBA_PrototypeGameModeBase.h"
#include "AIManager.h"
#include "Kismet/GameplayStatics.h"

void AMOBA_PrototypeGameModeBase::BeginPlay()
{
	
	
	//AIManager->SpawnBots(1, BotAbilities[0]);
	//AIManager->SpawnBots(1, BotAbilities[0]);
	//AIManager->SpawnBots(2, BotAbilities[1]);
	//AIManager->SpawnBots(2, BotAbilities[1]);
	//AIManager->SpawnGamePlayBots(BotAbilities);
}

void AMOBA_PrototypeGameModeBase::SpawnBotsFromGameMode()
{
	//AIManager = Cast<AAIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIManager::StaticClass()));
	//FindObjectOfClass(MyClass::StaticClass(), *ObjectName, true);
//AIManager = UGameplayStatics::FindObjectOfClass()
	if (AIManager) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AIManager Found ")));
		//AIManager->SpawnBots(1, BotAbilities[0]);
		//AIManager->SpawnBots(1, BotAbilities[0]);
	    //AIManager->SpawnBots(1, BotAbilities[0]);
	    //AIManager->SpawnBots(2, BotAbilities[1]);
	   // AIManager->SpawnBots(2, BotAbilities[1]);
		AIManager->SpawnGamePlayBots(BotAbilities);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AIManager Does Not Found ")));
	}
}
