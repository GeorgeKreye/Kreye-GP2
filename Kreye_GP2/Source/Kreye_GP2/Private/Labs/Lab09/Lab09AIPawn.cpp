// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab09/Lab09AIPawn.h"

#include "Labs/Lab09/Lab9AIMovementComponent.h"

// Sets default values
ALab09AIPawn::ALab09AIPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// Create movement component
	Movement = CreateDefaultSubobject<ULab9AIMovementComponent>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void ALab09AIPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALab09AIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALab09AIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
