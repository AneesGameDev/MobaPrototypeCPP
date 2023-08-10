// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectileClass.generated.h"

UCLASS()
class MOBA_PROTOTYPE_API ABulletProjectileClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectileClass();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileComponent;
     
	UPROPERTY()
		float ProjectileSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
	int32 BulletSpawnerID =1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireEnemy(FVector EnemyLocation, FVector ActorLocation);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
