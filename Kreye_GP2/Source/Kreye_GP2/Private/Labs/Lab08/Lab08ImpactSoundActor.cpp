// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab08/Lab08ImpactSoundActor.h"
#include "Components/AudioComponent.h"

// Sets default values
ALab08ImpactSoundActor::ALab08ImpactSoundActor()
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
	// 	Mesh->SetRelativeLocation(FVector::ZeroVector);
	//
	// 	// Set mesh to obey physics
	// 	Mesh->SetSimulatePhysics(true);
	// }
	//
	// // Get mesh material
	// auto Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(
	// 	TEXT("/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor"));
	// if (Material.Succeeded())
	// {
	// 	Mesh->SetMaterial(0, Material.Object);
	// }

	// Create audio component
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	Sound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Get impact sound effect
	auto ImpactSound = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT(
		"/Game/Labs/Lab08/Sound/566093__dundalkkirk__landing-softsurface.566093__dundalkkirk__landing-softsurface"));
	if (ImpactSound.Succeeded())
	{
		Sound->SetSound(ImpactSound.Object);
	}

	// Assign OnImpactHit to actor collision
	OnActorHit.AddDynamic(this,&ALab08ImpactSoundActor::OnImpactHit);

	// Tell mesh to check for hits
	Mesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void ALab08ImpactSoundActor::BeginPlay()
{
	Super::BeginPlay();

	// Make sure sound is inactive
	Sound->Stop();
}

// Called every frame
void ALab08ImpactSoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check whether to play the impact sound this tick
	if (PlaySoundThisTick)
	{
		// Tell audio component to play sound
		Sound->Play();
	}

	// Reset PlaySoundThisTick
	PlaySoundThisTick = false;
}

// Called when actor collides with something
void ALab08ImpactSoundActor::OnImpactHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit)
{
	// Play impact sound this tick
	PlaySoundThisTick = true;
}
