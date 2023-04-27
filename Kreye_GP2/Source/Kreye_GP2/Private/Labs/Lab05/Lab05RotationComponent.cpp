// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab05/Lab05RotationComponent.h"

#include "Serialization/ArchiveReplaceObjectRef.h"

// Sets default values for this component's properties
ULab05RotationComponent::ULab05RotationComponent() : RotationSpeed(1), RotationAxis(1.0,0.0,0.0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULab05RotationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULab05RotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate rotation change this tick & apply to root
	const FQuat RotationChange = FQuat(RotationAxis,RotationSpeed * DeltaTime);
	GetOwner()->GetRootComponent()->AddLocalRotation(RotationChange);
}

