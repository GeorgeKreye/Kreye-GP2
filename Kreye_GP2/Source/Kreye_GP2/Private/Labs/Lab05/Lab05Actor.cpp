// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab05/Lab05Actor.h"

// Sets default values
ALab05Actor::ALab05Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// Get mesh
	auto CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
		Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	}

	// Get material
	auto CubeMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/StarterContent/Materials/M_Metal_Chrome.M_Metal_Chrome"));
	if (CubeMaterial.Succeeded())
	{
		Mesh->SetMaterial(0,CubeMaterial.Object);
	}

}

// Called when the game starts or when spawned
void ALab05Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab05Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

