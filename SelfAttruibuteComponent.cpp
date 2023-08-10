// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfAttruibuteComponent.h"

// Sets default values for this component's properties
USelfAttruibuteComponent::USelfAttruibuteComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelfAttruibuteComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerHealth = DefaultHealth;

	// ...
	
}


// Called every frame
void USelfAttruibuteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USelfAttruibuteComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	
}

