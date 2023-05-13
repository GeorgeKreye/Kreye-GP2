// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab09/Lab9AIMovementComponent.h"

ULab9AIMovementComponent::ULab9AIMovementComponent() : MovementVelocity(50)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULab9AIMovementComponent::SetLastMovementInput(const FVector& Input)
{
	LastMovementInput = Input;
}
