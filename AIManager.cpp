// Fill out your copyright notice in the Description page of Project Settings.

#include "AIManager.h"
#include "MOBA_PrototypeGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "BotAbilities.h"
#include "SelfAttruibuteComponent.h"
#include "GruntsCPP.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAIManager::SpawnBots(int32 TeamId, TSubclassOf<AActor> Actor)
{
	FActorSpawnParameters SpawnParams;
	//UWorld* World = GetWorld();

		//for (int y = 0; y < PathsPoints[0].VectorArray.Num(); y++) {
		//	FPathPoint PathPoints;
		//	const FVector GlobalVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z);
		//	//PathsPoints[0].VectorArray[y] = GlobalVector;
		//	//WorldLocationPathPoints.Add(FVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z))

		//}
	FVector SpawnLocation;
	if (TeamId == 1) {
		SpawnLocation = FVector(GetActorLocation().X + PathsPoints[0].VectorArray[0].X, GetActorLocation().Y + PathsPoints[0].VectorArray[0].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[0].Z);
	}
	if (TeamId == 2) {
		int32 LastBaseIndes = PathsPoints[0].VectorArray.Num() -1;
		SpawnLocation = FVector(GetActorLocation().X + PathsPoints[0].VectorArray[LastBaseIndes].X, GetActorLocation().Y + PathsPoints[0].VectorArray[LastBaseIndes].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[LastBaseIndes].Z);
	}
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsBP, FTransform(SpawnLocation), SpawnParams);
	GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(200, 400);
	GruntBot->GruntTeamId = TeamId;
	GruntBot->BotAbility = Actor;
	//GruntBot->SetOwner()

	//GruntBot->ParticeEffect = Cast<ABotAbilities>(Actor.GetDefaultObject)
	if (HasAuthority()) {
		GruntBot->OnRep_TeamID();
	}
	//SpawnBotsOnClients(1, Actor, GruntBot);

	//GruntBot->GetMesh()->SetSkeletalMesh(GruntSkeletalA);
//	ChangeSkeletal(1, GruntBot);
	//GruntBot->BotAbility = Actor;

	////GruntBot->SetTeamId(TeamId);
	//GruntBot->GruntTeamId = 1;
	//USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
	//if (SelfComponent) {
	//	SelfComponent->OwnerHealth = 100.f;
	//	//SelfComponent->OwnerTeamID = 2;
	//}
	//GruntBot->OwnerHealth = 100.f;



	/* SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	 GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsBP, Transform, SpawnParams);
	 GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(500, 1000);*/
	 // GruntBot->GetMesh()->SetSkeletalMesh(GruntSkeletalB);
	 // ChangeSkeletal(2, GruntBot);
	  //GruntBot->BotAbility = Actor;

	  ////GruntBot->SetTeamId(TeamId);
	  //GruntBot->GruntTeamId = 2;

	  //SpawnBotsOnClients(2, Actor, GruntBot);



//   AActor* BotActor = World->SpawnActor<AActor>(Grunts, Transform.GetLocation() , Transform.GetRotation());

   //FTransform Transform = FTransform(SpawnLocation);


   //SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
   //AGruntsCPP* GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsA, Transform, SpawnParams);
   //GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(300, 600);
   //GruntBot->GruntTeamId = TeamId;

   //GruntBot->GruntPath = PathsPoints[0];

	if (TeamId == 1) {
		for (int y = 0; y < PathsPoints[0].VectorArray.Num(); y++) {
			FVector GlobalVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z);
			//GruntBot->GruntPath.VectorArray[y] = GlobalVector;
			GruntBot->GruntPath.VectorArray.Add(GlobalVector);

		}
	}
	else if (TeamId == 2)
	{

		for (int y = PathsPoints[0].VectorArray.Num() - 1; y >= 0; y--) {
			FVector GlobalVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z);
			//GruntBot->GruntPath.VectorArray[y] = GlobalVector;


			GruntBot->GruntPath.VectorArray.Add(GlobalVector);


		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Issue in AIManager.CPP : Line Number 62")));
		return;
	}


	//AActor* NewActor = World->SpawnActor<AActor>(Grunts, Transform.GetLocation(), Transform.GetRotation());
}

void AAIManager::SpawnBotsOnClients_Implementation(int32 TeamId, TSubclassOf<AActor> Actor, AGruntsCPP* GruntBotref)
{

		if (TeamId == 1)
		{
			//GruntBotref->GetMesh()->SetSkeletalMesh(GruntSkeletalA);
			GruntBotref->BotAbility = Actor;
			//GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(500, 1000);
			//GruntBot->SetTeamId(TeamId);
			GruntBot->GruntTeamId = 1;
			USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
			if (SelfComponent) {
				SelfComponent->OwnerHealth = 100.f;
				//SelfComponent->OwnerTeamID = 2;
			}
		}
		else if (TeamId == 2)
		{
			//GruntBotref->GetMesh()->SetSkeletalMesh(GruntSkeletalB);
			GruntBot->BotAbility = Actor;

			//GruntBot->SetTeamId(TeamId);
			GruntBot->GruntTeamId = 2;
			USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
			if (SelfComponent) {
				SelfComponent->OwnerHealth = 100.f;
				//SelfComponent->OwnerTeamID = 2;
			}

		}
	
}






void AAIManager::SpawnGamePlayBots(TArray<TSubclassOf<AActor>> Ability )
{
	FActorSpawnParameters SpawnParams;
	FTransform Transform;
	//int32 NextPathtoSpawnBot = 0;
	FVector GlobalVectorForward;
	FVector GlobalReverseVector;
	FPathPoint ForwardPathPoints;
	FPathPoint ReversePathPoints;
	//UWorld* World = GetWorld();

		//for (int y = 0; y < PathsPoints[0].VectorArray.Num(); y++) {
		//	FPathPoint PathPoints;
		//	const FVector GlobalVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z);
		//	//PathsPoints[0].VectorArray[y] = GlobalVector;
		//	//WorldLocationPathPoints.Add(FVector(GetActorLocation().X + PathsPoints[0].VectorArray[y].X, GetActorLocation().Y + PathsPoints[0].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[0].VectorArray[y].Z))

		//}	FVector SpawnLocation;


	//GruntBot->ParticeEffect = Cast<ABotAbilities>(Actor.GetDefaultObject)

	for (int NextPathtoSpawnBot = 0; NextPathtoSpawnBot < 3; NextPathtoSpawnBot++) {

		for (int y = 0; y < PathsPoints[NextPathtoSpawnBot].VectorArray.Num(); y++) {
			GlobalVectorForward = FVector(GetActorLocation().X + PathsPoints[NextPathtoSpawnBot].VectorArray[y].X, GetActorLocation().Y + PathsPoints[NextPathtoSpawnBot].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[NextPathtoSpawnBot].VectorArray[y].Z);
			//GruntBot->GruntPath.VectorArray[y] = GlobalVector;
			ForwardPathPoints.VectorArray.Add(GlobalVectorForward);
		}
		for (int y = PathsPoints[NextPathtoSpawnBot].VectorArray.Num() - 1; y >= 0; y--) {
			GlobalReverseVector = FVector(GetActorLocation().X + PathsPoints[NextPathtoSpawnBot].VectorArray[y].X, GetActorLocation().Y + PathsPoints[NextPathtoSpawnBot].VectorArray[y].Y, GetActorLocation().Z + PathsPoints[NextPathtoSpawnBot].VectorArray[y].Z);
			//GruntBot->GruntPath.VectorArray[y] = GlobalVector;


			ReversePathPoints.VectorArray.Add(GlobalReverseVector);
		}

		for (int i = 1; i <= 2; i++) {

			FVector SpawnLocation(GetActorLocation().X + PathsPoints[NextPathtoSpawnBot].VectorArray[0].X, GetActorLocation().Y + PathsPoints[NextPathtoSpawnBot].VectorArray[0].Y, GetActorLocation().Z + PathsPoints[NextPathtoSpawnBot].VectorArray[0].Z);
			Transform = FTransform(SpawnLocation);
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsBP, Transform, SpawnParams);
			//GruntBot->GetMesh()->SetSkeletalMesh(GruntSkeletalA);			
			GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(250, 500);
			

			USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
			if (SelfComponent) {
				SelfComponent->OwnerHealth = 100.f;
				//SelfComponent->OwnerTeamID = 1;
			}
			//GruntBot->GruntTeamId = 1;
			GruntBot->SetTeamId(1);
			GruntBot->GruntPath = ForwardPathPoints;
			if (i <= 2) {
				GruntBot->BotAbility = Ability[0];
			}
			else {
				GruntBot->BotAbility = Ability[1];
			}
			if (HasAuthority()) {
				GruntBot->OnRep_TeamID();
			}
			
		}
		for (int i = 1; i <= 2; i++) {

			int32 LastBaseIndes = PathsPoints[NextPathtoSpawnBot].VectorArray.Num();
			FVector SpawnLocation(GetActorLocation().X + PathsPoints[NextPathtoSpawnBot].VectorArray[LastBaseIndes - 1].X, GetActorLocation().Y + PathsPoints[NextPathtoSpawnBot].VectorArray[LastBaseIndes - 1].Y, GetActorLocation().Z + PathsPoints[NextPathtoSpawnBot].VectorArray[LastBaseIndes - 1].Z);
			Transform = FTransform(SpawnLocation);
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsBP, Transform, SpawnParams);
			//GruntBot->GetMesh()->SetSkeletalMesh(GruntSkeletalB);
			GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(250, 500);
			USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
			if (SelfComponent) {
				SelfComponent->OwnerHealth = 100.f;
				//SelfComponent->OwnerTeamID = 2;
			}
			//GruntBot->GruntTeamId = 2;
			GruntBot->SetTeamId(2);
			GruntBot->GruntPath = ReversePathPoints;
			//GruntBot->GruntTeamId = 2;
			if (i <= 1) {
				GruntBot->BotAbility = Ability[0];
			}
			else {
				GruntBot->BotAbility = Ability[1];
			}

			if (HasAuthority()) {
				GruntBot->OnRep_TeamID();
			}
			
		}

		ForwardPathPoints.VectorArray.Empty();
		ForwardPathPoints.VectorArray.Shrink();
		ReversePathPoints.VectorArray.Empty();
		ReversePathPoints.VectorArray.Shrink();
		
	}
	

	



	//   AActor* BotActor = World->SpawnActor<AActor>(Grunts, Transform.GetLocation() , Transform.GetRotation());

	   //FTransform Transform = FTransform(SpawnLocation);


	   //SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	   //AGruntsCPP* GruntBot = GetWorld()->SpawnActor<AGruntsCPP>(GruntsA, Transform, SpawnParams);
	   //GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(300, 600);
	   //GruntBot->GruntTeamId = TeamId;

	   //GruntBot->GruntPath = PathsPoints[0];

	//if (TeamId == 1) {
	//	
	//}
	//else if (TeamId == 2)
	//{

	//	
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Issue in AIManager.CPP : Line Number 62")));
	//	return;
	//}


	//AActor* NewActor = World->SpawnActor<AActor>(Grunts, Transform.GetLocation(), Transform.GetRotation());
}




// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	
	Super::BeginPlay();


	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld()->GetAuthGameMode());

	AMOBA_PrototypeGameModeBase* MyGameModeBase = Cast<AMOBA_PrototypeGameModeBase>(GameMode);

	// Use the game mode instance as needed
	if (MyGameModeBase != nullptr)
	{
		// Call a function in your custom game mode class
		MyGameModeBase->AIManager = this;
	}

	//AMOBA_PrototypeGameModeBase* GameModeBase = Cast<AMOBA_PrototypeGameModeBase>(GetWorld()->GetAuthGameMode());
	//GameModeBase->AIManager = this;
	

	//SpawnBots(1);
}

// Called every frame
void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AAIManager::ChangeSkeletal_Implementation(int32 TeamId, AGruntsCPP* GruntBotref)
//{
//	if (TeamId == 1)
//	{
//		GruntBotref->GetMesh()->SetSkeletalMesh(GruntSkeletalA);
//		GruntBotref->BotAbility = Actor;
//		GruntBot->GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::RandomIntegerInRange(500, 1000);
//		//GruntBot->SetTeamId(TeamId);
//		GruntBot->GruntTeamId = 1;
//		USelfAttruibuteComponent* SelfComponent = Cast<USelfAttruibuteComponent>(GruntBot->GetComponentByClass(USelfAttruibuteComponent::StaticClass()));
//		if (SelfComponent) {
//			SelfComponent->OwnerHealth = 100.f;
//			//SelfComponent->OwnerTeamID = 2;
//		}
//	}
//	else if (TeamId == 2)
//	{
//		GruntBotref->GetMesh()->SetSkeletalMesh(GruntSkeletalB);
//	}
//}