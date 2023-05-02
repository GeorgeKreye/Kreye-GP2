// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/Lab07Pawn.h"

// Sets default values
ALab07Pawn::ALab07Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALab07Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab07Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALab07Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

