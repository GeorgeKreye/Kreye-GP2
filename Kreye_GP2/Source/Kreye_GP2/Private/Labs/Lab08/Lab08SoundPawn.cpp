// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab08/Lab08SoundPawn.h"

// Sets default values
ALab08SoundPawn::ALab08SoundPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// Get mesh
	auto CylinderMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
		TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CylinderMesh.Object);
		Mesh->SetRelativeLocation(FVector::ZeroVector);
	}

	// Get mesh material
	auto Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(
		TEXT("/Game/StarterContent/Materials/M_Metal_Brushed_Nickel.M_Metal_Brushed_Nickel"));
	if (Material.Succeeded())
	{
		Mesh->SetMaterial(0, Material.Object);
	}
}

// Called when the game starts or when spawned
void ALab08SoundPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALab08SoundPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALab08SoundPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
