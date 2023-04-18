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
	SetRootComponent(StaticMesh);

	// Get mesh
	auto Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));
	if (Mesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(Mesh.Object);
	}
	
	// Get input action
	auto Action = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/PlayerMovementAction"));
	if (Action.Succeeded())
	{
		PlayerMovementAction = Action.Object;
	}

	auto Input = ConstructorHelpers::FObjectFinder<UInputMappingContext>(TEXT("/Game/Inputs/PlayerInputMapping"));
	if (Input.Succeeded())
	{
		PlayerInputMapping = Input.Object;
	}
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Assign and cast controller to a player controller
	if (TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!PlayerInputMapping.IsNull())
				{
					InputSystem->AddMappingContext(PlayerInputMapping.LoadSynchronous(),0);
				}
			}
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

