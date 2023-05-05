// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent() : MaxVelocity(40.0), PawnOwner(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMovementComponent::ConfirmPawnOwner()
{
	PawnOwner = true;
}

// Sets last movement input when called
void UPlayerMovementComponent::SetLastMovementInput(const FVector2d& Input)
{
	LastMovementInput = Input;
}

