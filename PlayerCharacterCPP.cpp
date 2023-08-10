// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GruntsCPP.h"
#include "BulletProjectileClass.h"
#include "Interface/TeamInterface.h"
#include "Components/CapsuleComponent.h"
#include "SelfAttruibuteComponent.h"
#include "AbilityActor.h"
#include "Public/AbilityController.h"
#include "GruntsAIControllerCPP.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
APlayerCharacterCPP::APlayerCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;
	//Camera->IsCollisionEnabled();

	TutnRateVal = 15.f;
	LookUpRatVal = 15.f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 50000.f , 0.f);

}

// Called when the game starts or when spawned
void APlayerCharacterCPP::BeginPlay()
{
	Super::BeginPlay();

	AbilityControllerObject = Cast<AAbilityController>(GetWorld()->SpawnActor<AAbilityController>(AbilityController));

	//MovementComponent = GetCharacterMovement();
	bGunIsAvailable = true;
	SelfAttribute = Cast<USelfAttruibuteComponent>(GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
	if (SelfAttribute) {
		SelfAttribute->OwnerHealth = SelfAttribute->DefaultHealth;
		SetTeamId(1);

	}

}

// Called every frame
void APlayerCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterCPP::MoveForward);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterCPP::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterCPP::TurnAtRate);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterCPP::LookUpRate);

	PlayerInputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &APlayerCharacterCPP::RightClickDown);
	//PlayerInputComponent->BindAction("LeftMouseClick", IE_Released, this, &APlayerCharacterCPP::RightClickUp);

	PlayerInputComponent->BindAction("RightMouseClick", IE_Pressed, this, &APlayerCharacterCPP::LeftClickDown);
	PlayerInputComponent->BindAction("RightMouseClick", IE_Released, this, &APlayerCharacterCPP::LeftClickUp);

	PlayerInputComponent->BindAction("one", IE_Pressed, this, &APlayerCharacterCPP::OneIsPressed);
	PlayerInputComponent->BindAction("one", IE_Released, this, &APlayerCharacterCPP::OneIsReleased);
	PlayerInputComponent->BindAction("two", IE_Pressed, this, &APlayerCharacterCPP::TwoIsPressed);
	PlayerInputComponent->BindAction("two", IE_Released, this, &APlayerCharacterCPP::TwoIsPressed);



}

void APlayerCharacterCPP::MoveForward(float Val)
{

	FRotator CharacterRotation = Controller->GetControlRotation();
	FRotator Rotation(0.f, CharacterRotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, Val);

}

void APlayerCharacterCPP::MoveRight(float Val)
{

	FRotator CharacterRotation = Controller->GetControlRotation();
	FRotator Rotation(0.f, CharacterRotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Val);

}

void APlayerCharacterCPP::LookUpRate(float Val)
{
	//FMath::Clamp(Val, 0.5, 0.5);
	//*LookUpRatVal* GetWorld()->DeltaTimeSeconds
	APlayerController* PController = Cast<APlayerController>(Controller);
	PController->PlayerCameraManager->ViewPitchMax = 20.f;
	PController->PlayerCameraManager->ViewPitchMin = -90.f;
	LookUpValue = Val * 20.f;
	AddControllerPitchInput(Val * LookUpRatVal*  GetWorld()->DeltaTimeSeconds);



}

void APlayerCharacterCPP::TurnAtRate(float Val)
{
	//*TutnRateVal* GetWorld()->DeltaTimeSeconds
	AddControllerYawInput(Val * TutnRateVal* GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacterCPP::LeftClickUp()
{
	bLeftClickDown = false;
}

void APlayerCharacterCPP::RightClickDown()
{
	if (AbilityControllerObject) {
		bRightClickDown = true;
	//	AttackingTimerDelay(1.f, EPrimaryAbilities::Fire, this, AbilityControllerObject);
	}
	if (bGunIsAvailable ) {
		
		//ShootingLineTrace();
		//AttackingAffect();
		//FireStoneWall();
		//DashAbility();
		
		//AbilityController->CallPrimaryAbility(EPrimaryAbilities::Fire, this);
	}

	if (bOneIsPRessed) {
		//Fire Stone Wall
	}

	if (bTwoIsPresed) {
		//Fire RayCast to Move Opposite Side
	}

}

void APlayerCharacterCPP::PrimaryAttackingTimerDelay(float TimeToDelay, EPrimaryAbilities Abilty, ACharacter* Character, AAbilityController* AbilityControllerr)
{
	FTimerDelegate Delegate;
		Delegate.BindLambda([Abilty, Character, AbilityControllerr] {
	
			AbilityControllerr->CallPrimaryAbility(Abilty, Character);
		   
			});
	
		GetWorldTimerManager().SetTimer(TimerDelay, Delegate, TimeToDelay, false);

}

void APlayerCharacterCPP::SecondaryAttackingTimerDelay(float TimeToDelay, ESecondaryAbilities Abilty, ACharacter* Character, AAbilityController* AbilityControllerr)
{
	FTimerDelegate Delegate;
	Delegate.BindLambda([Abilty, Character, AbilityControllerr] {

		AbilityControllerr->CallSecondaryAbility(Abilty, Character);

		});

	GetWorldTimerManager().SetTimer(TimerDelay, Delegate, TimeToDelay, false);

}

//void APlayerCharacterCPP::AttackingTimerDelay(float TimeToDelay, EPrimaryAbilities Abilty, ACharacter* Character, AAbilityController* AbilityController)
//{
//	
//}
void APlayerCharacterCPP::RightClickUp()
{
	bRightClickDown = false;
}

void APlayerCharacterCPP::OneIsPressed()
{
	bOneIsPRessed = true;
	bGunIsAvailable = false;
}

void APlayerCharacterCPP::OneIsReleased()
{
	bOneIsPRessed = false;
	bGunIsAvailable = true;

}

void APlayerCharacterCPP::TwoIsPressed()
{
	bTwoIsPresed = true;
	bGunIsAvailable = false;
}

void APlayerCharacterCPP::TwoIsReleased()
{
	bTwoIsPresed = false;
	bGunIsAvailable = true;
}

void APlayerCharacterCPP::SetTeamId(int32 Id)
{
	PlayerID = Id;
}

int32 APlayerCharacterCPP::GetTeamId()
{
	return PlayerID;
}

void APlayerCharacterCPP::TakeDamage(float DamageAmount)
{
	/*AActor* Player = Cast<AActor>(Actor);
	if (Player) {*/
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Damage Called on Line 194 , PlayerCharactercPP")));
		USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GetComponentByClass(USelfAttruibuteComponent::StaticClass()));

		if (SelfAttribute && SelfAttribute->OwnerHealth > 11) {
			SelfAttribute->OwnerHealth -= DamageAmount;
			OnHealthUpdated.Broadcast(SelfAttribute->OwnerHealth);
		}
		else if (SelfAttribute)
		{
			//AGruntsAIControllerCPP* AIController = Cast<AGruntsAIControllerCPP>(GetController());
			//if (ensure(AIController)) {
			//	AIController->NearestGrunt = nullptr;
			//	AIController->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
			//}
			
			//Destroy(this);
			DestroyActorOnServer();
		}

	
}
void APlayerCharacterCPP::DestroyActorOnServer_Implementation()
{
	this->Destroy(true);
}


void APlayerCharacterCPP::LeftClickDown()
{
	if (bGunIsAvailable) {
		bLeftClickDown = true;
	//	AttackingAffect();
		//ShootingLineTrace();
	}

}





void APlayerCharacterCPP::FireStoneWall()
{
	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);


	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);
	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);

	FVector EndLocation = Rotation.Vector() * 500;
	EndLocation += Location;

	//const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	ECollisionChannel TraceChannel;
	TraceChannel = ECollisionChannel::ECC_Pawn;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 

	bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel, Params);
	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel);

	if (LineTrace) {


		AActor* Actor = HitResult.GetActor();
		ITeamInterface* Interface = Cast<ITeamInterface>(Actor);

		if (!Interface) {

			UWorld* World = GetWorld(); // Get a reference to the world
			if (World)
			{
				FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 500.f); // Calculate the spawn location in front of the actor
				FRotator SpawnRotation = GetActorRotation(); // Use the actor's rotation
				AAbilityActor* WallAbility = World->SpawnActor<AAbilityActor>(WallActor, SpawnLocation, SpawnRotation); // Spawn the cube actor at the calculated location
				//CubeActor->SetOwner(this);
				WallAbility->SpawnerID = this->GetTeamId();
			}
		}
	}
	else {
		UWorld* World = GetWorld(); // Get a reference to the world
		if (World)
		{
			FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 500.f); // Calculate the spawn location in front of the actor
			FRotator SpawnRotation = GetActorRotation(); // Use the actor's rotation
			AAbilityActor* WallAbility = World->SpawnActor<AAbilityActor>(WallActor, SpawnLocation, SpawnRotation); // Spawn the cube actor at the calculated location
			WallAbility->SpawnerID = this->GetTeamId();
		}
	}
}

	//FVector EndLocation = Rotation.Vector() * 1500;
	//EndLocation += Location;

	////const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	//ECollisionChannel TraceChannel;
	//TraceChannel = ECollisionChannel::ECC_Visibility;
	//FCollisionQueryParams Params;// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 
	////bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel , Params);
	//bool LineTrace = GetWorld()->LineTraceSingleByProfile(HitResult, Location, EndLocation, "Bullethit");

	//if (LineTrace) {

	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LineTraceInnerFunction Is Called"));
	//	//DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, 10.f);
	//	HitResult.GetComponent()->AddImpulse(HitResult.Normal * (HitResult.GetComponent()->GetMass()) * -500);
	//	AGruntsCPP* Grunt = Cast<AGruntsCPP>(HitResult.GetActor());
	//	if (Grunt && Grunt->GruntTeamId != this->PlayerID) {

	//		Grunt->GiveDamage(Grunt, 10.f);

	//	}
	//	else
	//	{
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Zombie Character Not Collide"));
	//	}
	//}





void APlayerCharacterCPP::PushAbilityRemove(ACharacter* CharactertoRemovePhysics)
{
	CharactertoRemovePhysics->GetCapsuleComponent()->SetSimulatePhysics(true);

}
void APlayerCharacterCPP::PushAbility()
{
	
	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);


	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);
	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);

	FVector EndLocation = Rotation.Vector() * 1500;
	EndLocation += Location;

	//const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	ECollisionChannel TraceChannel;
	TraceChannel = ECollisionChannel::ECC_Pawn;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 

	bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel , Params);
	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel);

	if (LineTrace) {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LineTraceInnerFunction Is Called"));
		DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, 10.f);
		
		AActor* Actor = HitResult.GetActor();
		ITeamInterface* Interface = Cast<ITeamInterface>(Actor);
		//&& Interface->GetTeamId() != this->GetTeamId()
		if (Interface ) {
			//GetComponentByClass(Actor)
			//Actor->AddIm(HitResult.Normal * -100000);
			ACharacter* Character = Cast<ACharacter>(Actor);
			if (Character) {
				FVector HitNormal = HitResult.Normal; // Assuming you have a HitResult object from the hit event
				FVector OppositeDirection = -1 * HitNormal;
				//Character->GetCapsuleComponent()->SetSimulatePhysics(true);
				//bPushForceCount = 100;
				Character->GetCapsuleComponent()->SetSimulatePhysics(true);
				Character->GetCapsuleComponent()->AddImpulse(HitResult.Normal * -100000);
				FTimerDelegate Delegate;
				Delegate.BindLambda([Character] {Character->GetCapsuleComponent()->SetSimulatePhysics(false);
				//Character->SetActorLocation(Character->GetActorLocation());
				//bPushForce = false;
					});
				GetWorldTimerManager().SetTimer(TimerDelay, Delegate, 3.f, false);
				//FVector CurrentLocation = Character->GetActorLocation();

		/*		while (bPushForceCount<500)
				{
					bPushForceCount++;
					FVector NewLocation = CurrentLocation + OppositeDirection * 2.f;
					Character->SetActorLocation(NewLocation);
				}*/

				 // Assuming you have a reference to your character
				 // DistanceToMove is the amount you want to move opposite to the hit normal
				
				bPushForceCount = 0;
			
				
				//
				//GetWorldTimerManager().SetTimer(TimerDelay, this, &APlayerCharacterCPP::PushAbilityRemove, 1.0f, false);
				
			}
			//if (BulletSpawnerID != Interface->GetTeamId()) {
			//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("Line 54  BulletProjectileClass , Damage 20 Run")));
			//	Interface->TakeDamage(OtherActor, 5.0);
			//}
			

		}
		/*AGruntsCPP* Grunt = Cast<AGruntsCPP>(HitResult.GetActor());
		if (Grunt && Grunt->GruntTeamId != this->PlayerID) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit Result Found Grunt Found Line 300, PlayerCharacterCPP"));
			Grunt->GiveDamage(Grunt, 10.f);
			
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Grunt Attacking Not Found Line 300, PlayerCharacterCPP"));
		}*/

	}
	RightClickUp();
}
void APlayerCharacterCPP::DashAbility()
{
	UCharacterMovementComponent* MovementComponent;
	MovementComponent = GetCharacterMovement();
	if (MovementComponent) {
		GetCharacterMovement()->MaxWalkSpeed = 10000.f;
		GetCharacterMovement()->MaxAcceleration = 5000.f;
		GetCharacterMovement()->BrakingFriction = 2000.f;
	}
	
	FTimerDelegate Delegatee;
	Delegatee.BindLambda([MovementComponent] {
	MovementComponent->MaxWalkSpeed = 1000.f;
	MovementComponent->MaxAcceleration = 2400.f;
	MovementComponent->BrakingFriction = 0.f;
		});
	GetWorldTimerManager().SetTimer(TimerDelay, Delegatee, 0.5f, false);
	

}

void APlayerCharacterCPP::ShootingLineTrace()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("ShootingLineTrace is Called")));
	FVector Location;
	FRotator Rotation;
	FRotator SpawnRotation;
	Controller->GetPlayerViewPoint(Location, Rotation);
	//Rotation.Vector()+FVector(0.f,-185.f,0.f);
	FRotator RotationOffset = FRotator(0.f, 5.f, 0.f); // Set the rotation offset to (0, 45, 0)
	Rotation += RotationOffset;

	///FVector ForwardVector = Rotation.GetComponentForAxis(EAxis::X);
	//Rotation.Add(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
	//SpawnRotation = GetActorForwardVector().Rotation();
	//SpawnRotation.Add(0.0f, 90.f, 0.0f);
	//Rotation = GetActorForwardVector().Rotation().Add(GetActorForwardVector().Rotation().Pitch + LookUpValue, GetActorForwardVector().Rotation().Yaw, GetActorForwardVector().Rotation().Roll);
	ABulletProjectileClass* BulletProjectile;
	BulletProjectile = Cast<ABulletProjectileClass>(GetWorld()->SpawnActor<ABulletProjectileClass>(BulletPrefab, GetMesh()->GetSocketLocation("ShootingLocation"), Rotation));
	
	if (BulletProjectile) {
		BulletProjectile->BulletSpawnerID = this->GetTeamId();		
	}
	RightClickUp();
	
	//CameraShakeEvent();
/*	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);


	//Location =  FVector(Location.X - 20,Location.Y , Location.Z);

	FVector EndLocation = Rotation.Vector() * 1500;
	EndLocation += Location;

	//const FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;

	ECollisionChannel TraceChannel;
	TraceChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams Params;// FCollisionQueryParams::; /* = FCollisionQueryParams::DefaultQueryParam  = FCollisionResponseParams::DefaultResponseParam 
	//bool LineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, TraceChannel , Params);
	bool LineTrace = GetWorld()->LineTraceSingleByProfile(HitResult, Location, EndLocation, "Bullethit");
	
	if (LineTrace) {

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LineTraceInnerFunction Is Called"));
		//DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Red, true, 10.f);
		HitResult.GetComponent()->AddImpulse(HitResult.Normal * (HitResult.GetComponent()->GetMass()) * -500);
		 AGruntsCPP* Grunt= Cast<AGruntsCPP>(HitResult.GetActor());
		if (Grunt && Grunt->GruntTeamId != this->PlayerID) {

			Grunt->GiveDamage(Grunt, 10.f);

		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Zombie Character Not Collide"));
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LineTraceOuterFunction Is Called"));
	*/
}

void APlayerCharacterCPP::StartSwordAttack() {


	USkeletalMeshComponent* Sword = Cast<USkeletalMeshComponent>(GetMesh()->GetChildComponent(0));
	if (Sword) {


		FVector Start = Sword->GetSocketLocation("Start");
		FVector End = Sword->GetSocketLocation("End");


		FHitResult HitResult;

		FCollisionObjectQueryParams CC;
		CC.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.f);
		//Perform the line trace against the object//, FCollisionQueryParams()
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, CC, TraceParams))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Attack Trace Run")));
			//	// Handle the hit result
			if (auto HitActor = HitResult.GetActor()) {

				if (auto EnemyHitGrunt = Cast<AGruntsCPP>(HitActor)) {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Attack Trace Run")));
					//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplodeGrenadeParticals,Location);

					//if (!ParticeIsPlaying) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ABotAbilities>(BotAbility->GetDefaultObject())->ParticeEffect, HitResult.Location);
					//GiveDamage(EnemyHitGrunt , Cast<ABotAbilities>(EnemyHitGrunt->BotAbility->GetDefaultObject())->DamageAmount);
					//ParticeIsPlaying = true;
					// The line trace hit the object
				}
			}
		}




	}


	//FVector StartLocation = GetMesh()->GetSocketLocation("StartLocation_Attack");
	//FVector EndLocation = GetMesh()->GetSocketLocation("EndLocation_Attack");
	// Get the player controller
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Attack Line Trace Called")));

	//// Get the camera location and forward vector
	//if (!StartBool)
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Start Bool is  :: False ")));
	//	ParticeIsPlaying = false;
	//	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	//}



	

}
