// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab06/Lab06Pawn.h"

// Sets default values
ALab06Pawn::ALab06Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Get default pawn mesh
	auto CapsuleMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (CapsuleMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CapsuleMesh.Object);
		Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	}
	
	// Get default pawn material
	auto PawnMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor"));
	if(PawnMaterial.Succeeded())
	{
		Mesh->SetMaterial(0,PawnMaterial.Object);
	}
}

// Called when the game starts or when spawned
void ALab06Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab06Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALab06Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when movement is inputted
void ALab06Pawn::Move(const FInputActionInstance& Instance)
{
	
}


