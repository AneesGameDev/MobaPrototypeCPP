// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/List.h"
#include "PathPoint.h"
#include "GruntsCPP.h"
#include "AIManager.generated.h"


UCLASS()




class MOBA_PROTOTYPE_API AAIManager : public AActor
{
	GENERATED_BODY()
	
	//enum PathName
	//{
	//	LeftPath,
	//	MiddlePath,
	//	RightPath
	//};

	//USTRUCT(BlueprintType)
	//	struct FMyStruct
	//{
	//	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	//		TArray<FVector> PathPoints;
	//};

public:	
	// Sets default values for this actor's properties
	AAIManager();
	//, meta = (MakeEditWidget = true)
	UPROPERTY(EditAnywhere )
	TArray<FPathPoint> PathsPoints;
	UPROPERTY(EditAnywhere, Category = "BotReference");
	TSubclassOf<AActor> GruntsBP;
	/*UPROPERTY(EditAnywhere, Category = "BotReference");
	TSubclassOf<AActor> GruntsB;*/


	class AGruntsCPP* GruntBot;

	TArray<FPathPoint> WorldLocationPathPoints;




	/*UFUNCTION(Server,Reliable)
		void test();

	UFUNCTION(NetMulticast, Reliable)
		void vhghgj();*/




	
	UFUNCTION(BlueprintCallable, Category = "SpwnedBots")
		void SpawnBots(int32 TeamId , TSubclassOf<AActor> Actor);

	UFUNCTION(NetMulticast, Reliable)
		void SpawnBotsOnClients(int32 TeamId, TSubclassOf<AActor> Actor , AGruntsCPP* GruntBotref);
	

	UFUNCTION()
		void SpawnGamePlayBots(TArray<TSubclassOf<AActor>> Ability);

	//UFUNCTION(NetMulticast, Reliable)
		//void ChangeSkeletal(int32 TeamId, AGruntsCPP* GruntBotref , TSubclassOf<AActor> Actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
