// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TeamInterface.h"
#include "DefenceTower.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefenceHealthChange, float, Value);
UCLASS()
class MOBA_PROTOTYPE_API ADefenceTower : public AActor , public ITeamInterface
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ADefenceTower();
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		FVector VectorArray;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefecneTowerID")
		int32 TowerID;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionComponent* sight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Sight* SightConfig;

	//UPROPERTY(EditAnywhere)
	//	 UStaticMeshComponent* TowerBaseCylinder;

	UPROPERTY(EditAnywhere)
		 UStaticMeshComponent* FireBeamMesh;
	//BulletProjectileClass* Bullet;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BulletPrefab;
	//float DelayTime = 2.5;

	float CurrentTimeInSeconds;
	float PreviousTimeDelay;
	//class BulletProjectileClass* Bullet;
	UPROPERTY()
	TArray<class AActor*> ActorsRef;

	FTimerHandle TimerHandle;

	float DelayTime = 0.5f;

	UPROPERTY()
		class USelfAttruibuteComponent* SelfAttribute;

	UPROPERTY(BlueprintAssignable)
		FOnDefenceHealthChange OnHealthUpdated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		 void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
		void SpawnBulletsEverySeconds();

	


	// Inherited via ITeamInterface
	UFUNCTION()
	virtual void SetTeamId(int32 Id) override;
	UFUNCTION()
	virtual int32 GetTeamId() override;
	UFUNCTION()
	virtual void TakeDamage( float DamageAmount) override;

	/*UFUNCTION(BlueprintCallable)
		void ShootProjectile(FVector Location , )*/
};
