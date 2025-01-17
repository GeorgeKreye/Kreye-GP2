// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab03/RotatorComponent.h"

// Sets default values for this component's properties
URotatorComponent::URotatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get owner
	Owner = GetOwner();
}


// Called when the game starts
void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Increment rotation
	const FRotator CurrentRotation = Owner->GetActorRotation();
	FRotator NewRotation = FRotator(CurrentRotation);
	NewRotation += FRotator(0.0,RotationSpeed * DeltaTime,0.0);
	Owner->SetActorRotation(NewRotation);
	
}

