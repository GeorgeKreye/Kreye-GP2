// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/Lab07Trigger.h"
#include "Kreye_GP2/Kreye_GP2.h"

// Sets default values
ALab07Trigger::ALab07Trigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// // Get cube mesh
	// auto CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(
	// 	TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	// if (CubeMesh.Succeeded())
	// {
	// 	Mesh->SetStaticMesh(CubeMesh.Object);
	// 	Mesh->SetRelativeLocation(FVector::ZeroVector);
	// }
	//
	// // Get material
	// auto Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(
	// 	TEXT("/Game/StarterContent/Materials/M_Metal_Copper.M_Metal_Copper"));
	// if (Material.Succeeded())
	// {
	// 	Mesh->SetMaterial(0, Material.Object);
	// }

	// Assign OnTriggerHit to actor collision
	OnActorHit.AddDynamic(this, &ALab07Trigger::OnTriggerHit);

	// Tell mesh to check for hits
	Mesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void ALab07Trigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALab07Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when trigger has been hit
void ALab07Trigger::OnTriggerHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit)
{
	LOG("Trigger has been hit");
}
