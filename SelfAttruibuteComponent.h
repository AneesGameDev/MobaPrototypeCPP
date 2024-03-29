// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelfAttruibuteComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBA_PROTOTYPE_API USelfAttruibuteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelfAttruibuteComponent();
	/*UPROPERTY(VisibleAnywhere, Category = "AttachedCharacterId")
		int32 OwnerTeamID =0;*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttacherCharacterHealth")
	int32 OwnerHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttacherCharacterHealth")
	int32 DefaultHealth=100;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
