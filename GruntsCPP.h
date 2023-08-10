// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PathPoint.h"
#include "Delegates/Delegate.h"
#include "Interface/TeamInterface.h"
#include "GruntsCPP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float, Value);
UCLASS()
class MOBA_PROTOTYPE_API AGruntsCPP : public ACharacter , public ITeamInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGruntsCPP();
	/*UPROPERTY(EditAnywhere, Category = "HealthBaarWidget");
	TSubclassOf<UUserWidget> HealthWidget;
	UPROPERTY(EditAnywhere, Category = "HealthBaarWidget");
	class UUserWidget* HelathBaarWidget;*/

	UPROPERTY(BlueprintReadWrite, Category = "PauseResume")
		bool IsPauseBT;

	UPROPERTY(EditAnywhere , BlueprintReadWrite,ReplicatedUsing = OnRep_TeamID)
	int32 GruntTeamId=0;
	UPROPERTY(EditAnywhere)
	int32 BotHealth;

	UPROPERTY(EditAnywhere, Category = "BotReference");
	USkeletalMesh* GruntSkeletalA;
	UPROPERTY(EditAnywhere, Category = "BotReference");
	USkeletalMesh* GruntSkeletalB;

	UFUNCTION()
		void OnRep_TeamID();

	UPROPERTY(EditAnywhere)
	int32 SelectedPathOfGrunt;
	UPROPERTY(EditAnywhere)
	FPathPoint GruntPath;

	UPROPERTY(EditAnywhere)
	int32 CurrentMovedIndex;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABotAbilities> BotAbility;


	UPROPERTY(EditAnywhere)
	UAnimMontage* Atteck;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ParticeEffectt;

	UPROPERTY()
		ABotAbilities* BotAbiliyTemp;

	UFUNCTION(NetMulticast, Reliable,  BlueprintCallable)
		void Atteck_Anim_Play();

	//UFUNCTION(NetMulticast, Reliable)
	//	void AttackAnimReplication();

	UPROPERTY(BlueprintReadWrite, Category = "StartBool")
		bool StartBool= false;

	bool ParticeIsPlaying =false;
	 FTimerHandle MyTimerHandle;

	 int32 AttackCounter;
	 UPROPERTY(EditAnywhere , Category = "AttackParticele")
	 UParticleSystem* AttackParticle;
	 UPROPERTY(EditAnywhere, BlueprintReadWrite , Category ="BoxCollisionComponent")
	class UBoxComponent* BoxComponent;

	UFUNCTION(BlueprintCallable)
		void MoveToNextTarget(FVector &OutLocation);
	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintNativeEvent, Category = "AttackBotsEvent");
	void AttackLineTrace();
	
	UFUNCTION(BlueprintCallable , Category="AttackFunction")
	void AttackLineTraceTime();

	UFUNCTION(BlueprintCallable, Category = "GiveDamageFunction")
	void GiveDamage(AGruntsCPP* Grunt ,float value);
	//UPROPERTY(BlueprintAssignable, Category = "Health")
	//FHealthBarUpdateDelegate OnHealthUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthUpdated;
	UFUNCTION()
	virtual void SetTeamId(int32 Id) override;

	

	// Inherited via ITeamInterface
	UFUNCTION()
	virtual int32 GetTeamId() override;

	//UPROPERTY(Server , Reliable)
	UFUNCTION()
	virtual void TakeDamage(float DamageAmount) override;
	UFUNCTION(Server, Reliable)
		void DestroyActorOnServer();

	/*UPROPERTY(NetMulticast, Reliable)
		void TakeDamageMulticast(float DamageAmount);*/
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
