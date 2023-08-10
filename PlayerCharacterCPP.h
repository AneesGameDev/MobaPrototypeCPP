// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/TeamInterface.h"
#include "public/AbilityController.h"
#include "PlayerCharacterCPP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHealthChange, float, Value);
UCLASS()
class MOBA_PROTOTYPE_API APlayerCharacterCPP : public ACharacter , public ITeamInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlayerCharacterCPP();


	UPROPERTY(EditAnywhere, Category = "AbilityController")
		TSubclassOf<AAbilityController> AbilityController;

	UPROPERTY(BlueprintReadWrite , Category="AbilityController")
		AAbilityController* AbilityControllerObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcces = "ture"))
	class USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float LookUpRatVal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TutnRateVal;

	UPROPERTY(VisibleAnywhere)
	int32 PlayerID =0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LeftClickGet")
		bool bLeftClickDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RightClickGet")
		bool bRightClickDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bGunIsAvailable;
	UPROPERTY()
		bool bOneIsPRessed = false;
	UPROPERTY()
		bool bTwoIsPresed = false;

	int32 bPushForceCount;


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> WallActor;

	UFUNCTION(BlueprintCallable, Category = "ShootingClick")
		void ShootingLineTrace();


	UFUNCTION(BlueprintCallable, Category = "StoneWall")
		void FireStoneWall();


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BulletPrefab;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookUpValue;

	UPROPERTY()
		class USelfAttruibuteComponent* SelfAttribute;

	FTimerHandle TimerDelay;
	FTimerHandle TimerDelayPushAffect;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Function Used for Move Forward and Backward of player
	void MoveForward(float Val);
	
	//Function used for character movement left and right
	void MoveRight(float Val);

	//used for mouse look up and down 
	void LookUpRate(float Rate);

	//used for mouse look right and left with some specific rate
	void TurnAtRate(float Rate);

	UPROPERTY(BlueprintAssignable)
		FOnPlayerHealthChange OnHealthUpdated;


	//UPROPERTY(EditAnywhere)
		//UCharacterMovementComponent* MovementComponent;


	UFUNCTION()
		void LeftClickDown();

	UFUNCTION()
		void LeftClickUp();
	UFUNCTION(BlueprintCallable, Category = "ShootingClick")
		void RightClickDown();

	UFUNCTION(BlueprintCallable, Category = "ShootingClick")
		void RightClickUp();

	UFUNCTION()
		void OneIsPressed();

	UFUNCTION()
		void OneIsReleased();

	UFUNCTION()
		void TwoIsPressed();

	UFUNCTION()
		void TwoIsReleased();

	// Inherited via ITeamInterface
	UFUNCTION()
	 void SetTeamId(int32 Id) override;

	UFUNCTION()
     int32 GetTeamId() override;
	UFUNCTION()
	 void TakeDamage(float DamageAmount) override;

	UFUNCTION(Server, Reliable)
		void DestroyActorOnServer();

	UFUNCTION(BlueprintCallable , Category ="CallToAbilityController")
	void PrimaryAttackingTimerDelay(float TimeToDelay , EPrimaryAbilities Abilty , ACharacter* Character, AAbilityController* AbilityControllerr);

	UFUNCTION(BlueprintCallable, Category = "CallToAbilityController")
		void SecondaryAttackingTimerDelay(float TimeToDelay, ESecondaryAbilities Abilty, ACharacter* Character, AAbilityController* AbilityControllerr);


	void PushAbilityRemove(ACharacter* CharactertoRemovePhysics);

	void PushAbility();

	void DashAbility();

	UFUNCTION(BlueprintCallable, Category ="StartSwordAttack")
	void StartSwordAttack();

};
