// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Perspective/Perspective.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	// Get mesh
	auto Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (Mesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(Mesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	} else
	{
		WARN("ERROR: Could not find mesh");
	}

	// Get mesh material
	auto Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>
		(TEXT("/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor"));
	if (Material.Succeeded())
	{
		StaticMesh->SetMaterial(0,Material.Object);
	} else
	{
		WARN("ERROR: Could not find mesh material");
	}
	
	// Get input action
	auto Action = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/PlayerMovementAction.PlayerMovementAction"));
	if (Action.Succeeded())
	{
		PlayerMovementAction = Action.Object;
	} else
	{
		WARN("ERROR: Could not find movement action");
	}

	// Get input mapping
	auto Input = ConstructorHelpers::FObjectFinder<UInputMappingContext>
		(TEXT("/Game/Inputs/PlayerInputMapping.PlayerInputMapping"));
	if (Input.Succeeded())
	{
		PlayerInputMapping = Input.Object;
	} else
	{
		WARN("ERROR: Could not find input mapping");
	}
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Assign and cast controller to a player controller
	if (const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!PlayerInputMapping.IsNull())
				{
					InputSystem->AddMappingContext(PlayerInputMapping.LoadSynchronous(),0);
				} else
				{
					WARN("Mapping already exists!");
				}
			} else
			{
				WARN("Mapping failed at input system retrieval!");
			}
		} else
		{
			WARN("Mapping failed at local player retrieval!");
		}
	} else
	{
		WARN("Mapping failed at controller cast!");
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move player if movement has been received
	const FVector LastInput3D = FVector(LastInput.X,LastInput.Y,0);
	const FVector UpdatedLocation = GetActorLocation() + LastInput3D;
	if (UpdatedLocation != GetActorLocation())
	{
		LOG("New location: (%d,%d,$d)",UpdatedLocation.X,UpdatedLocation.Y,UpdatedLocation.Z);
	}
	SetActorLocation(UpdatedLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	WARN("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	WARN("Binding move actions");
	EIS->BindAction(PlayerMovementAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
}

void APlayerPawn::Move (const struct FInputActionInstance& Instance)
{
	LastInput = Instance.GetValue().Get<FVector2d>();
	LOG("Move input: (%f, %f)",LastInput.X,LastInput.Y);
}

