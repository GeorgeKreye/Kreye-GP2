// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab03/SineBounceComponent.h"

// Sets default values for this component's properties
USineBounceComponent::USineBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get owner
	Owner = GetOwner();
}


// Called when the game starts
void USineBounceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USineBounceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate Z increment
	const double NewZ = BounceAmplitude * sin(GetWorld()->GetTimeSeconds());

	// Calculate new location and move actor
	FVector NewLocation = Owner->GetActorLocation();
	NewLocation += FVector(0.0,0.0,NewZ);
	Owner->SetActorLocation(NewLocation);
}

