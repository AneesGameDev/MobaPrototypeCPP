// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectileClass.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GruntsCPP.h"
#include "PlayerCharacterCPP.h"

// Sets default values
ABulletProjectileClass::ABulletProjectileClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(GetRootComponent());
	BulletMesh->SetSimulatePhysics(true);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));


}

// Called when the game starts or when spawned
void ABulletProjectileClass::BeginPlay()
{
	Super::BeginPlay();

	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABulletProjectileClass::OnOverlapBegin);
}

// Called every frame
void ABulletProjectileClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("Line 34  BulletProjectileClass Bullet Spawner ID , %d"), BulletSpawnerID));
}

void ABulletProjectileClass::FireEnemy(FVector EnemyLocation , FVector ActorLocation)
{

	
		// Calculate the initial velocity of the projectile based on the enemy's location
		FVector Direction = EnemyLocation - ActorLocation;
		Direction.Normalize();
		//ProjectileComponent->SetVelocityInLocalSpace(Direction * ProjectileSpeed);
	
}

void ABulletProjectileClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Defence Tower Detect Grunt an Make Rotation on Line 81, DefenceTower.cpp")));
	ITeamInterface* Interface = Cast<ITeamInterface>(OtherActor);
	if (Interface) {
		if (BulletSpawnerID != Interface->GetTeamId()) {
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("Line 54  BulletProjectileClass , Damage 20 Run")));
			Interface->TakeDamage(10.0);			
		}
	}

	//AGruntsCPP* Grunt = Cast<AGruntsCPP>(OtherActor);
	//APlayerCharacterCPP* Player = Cast<APlayerCharacterCPP>(OtherActor);
	//if (Player) {
	//	//Player->TakeDamage()
	//}
	//else if(Grunt)
	//{
	//	Grunt->GiveDamage(Grunt, 5.f);
	//}
	if (OtherActor != this) {
		this->Destroy();
	}
	
	this->Destroy();

}

