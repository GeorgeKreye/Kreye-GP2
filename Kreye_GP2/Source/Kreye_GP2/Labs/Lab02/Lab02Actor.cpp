// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab02Actor.h"

// Sets default values
ALab02Actor::ALab02Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	// Get sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	
	if (SphereVisualAsset.Succeeded())
	{
	  	Mesh->SetStaticMesh(SphereVisualAsset.Object);
	 	Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	}
	
	// Get mesh material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		SphereMaterial(TEXT("/Game/StarterContent/Materials/M_Cobblestone_Pebble"));
	
	if (SphereMaterial.Succeeded())
	{
	 	Mesh->SetMaterial(0, SphereMaterial.Object);
	}
}

// Called when the game starts or when spawned
void ALab02Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab02Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

