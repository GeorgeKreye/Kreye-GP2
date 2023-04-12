// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab03/Lab03Actor.h"

// Sets default values
ALab03Actor::ALab03Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Get cube mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(CubeVisualAsset.Object);
		Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	}

	// Get mesh material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		CubeMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Steel"));
	if (CubeMaterial.Succeeded())
	{
		Mesh->SetMaterial(0,CubeMaterial.Object);
	}
}

// Called when the game starts or when spawned
void ALab03Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab03Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

