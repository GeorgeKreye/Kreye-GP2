// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/MovingPhysicsObject.h"

// Sets default values
AMovingPhysicsObject::AMovingPhysicsObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// // Get mesh
	// auto CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
	// 	TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	// if (CubeMesh.Succeeded())
	// {
	// 	Mesh->SetStaticMesh(CubeMesh.Object);
	// 	Mesh->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
	//
	// 	// Modify scale to alter mesh into platform shape
	// 	Mesh->SetRelativeScale3D(FVector(1.5, 1.5, 0.25));
	// }
	//
	// // Get mesh texture
	// auto MeshTexture = ConstructorHelpers::FObjectFinder<UMaterialInterface>(
	// 	TEXT("/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor"));
	// if (MeshTexture.Succeeded())
	// {
	// 	Mesh->SetMaterial(0,MeshTexture.Object);
	// }
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
