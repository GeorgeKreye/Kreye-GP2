// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/MovingPhysicsObject.h"

// Sets default values
AMovingPhysicsObject::AMovingPhysicsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPhysicsObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPhysicsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

