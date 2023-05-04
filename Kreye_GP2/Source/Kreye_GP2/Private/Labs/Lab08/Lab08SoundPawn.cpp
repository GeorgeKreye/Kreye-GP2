// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab08/Lab08SoundPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AudioComponent.h"
#include "Kreye_GP2/Kreye_GP2.h"

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

	// Create audio component
	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	Sound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Get sound
	auto SoundEffect = ConstructorHelpers::FObjectFinder<USoundWave>(
		TEXT("/Game/Labs/Lab08/Sound/321103__nsstudios__blip1.321103__nsstudios__blip1"));
	if (SoundEffect.Succeeded())
	{
		Sound->SetSound(SoundEffect.Object);
	}

	// Create music component
	Music = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));
	Music->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);

	// Get music
	auto BackgroundMusic = ConstructorHelpers::FObjectFinder<USoundWave>(TEXT("/Game/Labs/Lab08/Sound/Clouds.Clouds"));
	if (BackgroundMusic.Succeeded())
	{
		Music->SetSound(BackgroundMusic.Object);
	}
	
	// Get sound playing action
	auto InputAction = ConstructorHelpers::FObjectFinder<UInputAction>(
		TEXT("/Game/Labs/Lab08/Input/Lab08PlaySoundAction.Lab08PlaySoundAction"));
	if (InputAction.Succeeded())
	{
		PlaySoundAction = InputAction.Object;
	}

	// Get input mapping context
	auto InputMappingContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(
		TEXT("/Game/Labs/Lab08/Input/Lab08InputMappingContext.Lab08InputMappingContext"));
	if (InputMappingContext.Succeeded())
	{
		InputMap = InputMappingContext.Object;
	}
}

// Called when the game starts or when spawned
void ALab08SoundPawn::BeginPlay()
{
	Super::BeginPlay();

	// Make sure sound is inactive
	Sound->Stop();

	// Play music
	Music->Play();

	// Assign and cast controller to a player controller
	LOG("Attempting to set up input mapping to controller");
	if (const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!InputMap.IsNull())
				{
					InputSystem->AddMappingContext(InputMap.LoadSynchronous(), 0);
				}
				else
				{
					WARN("ERROR: No mapping context to use! (InputMap is null)");
				}
			}
			else
			{
				WARN("ERROR: Mapping failed at input system retrieval!");
			}
		}
		else
		{
			WARN("ERROR: Mapping failed at local player retrieval!");
		}
	}
	else
	{
		WARN("ERROR: Mapping failed at controller cast!");
	}
}

// Called every frame
void ALab08SoundPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check whether to play a sound this frame
	if (PlaySoundThisTick)
	{
		// Tell audio component to play sound
		Sound->Play();
	}

	// Reset PlaySoundThisTick
	PlaySoundThisTick = false;
}

// Called to bind functionality to input
void ALab08SoundPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get enhanced input component
	LOG("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind play sound action to enhanced input component
	LOG("Binding move action");
	EIS->BindAction(PlaySoundAction, ETriggerEvent::Triggered, this, &ALab08SoundPawn::SoundTriggered);
}

// Called when sound is triggered by pressing spacebar
void ALab08SoundPawn::SoundTriggered(const FInputActionInstance& Instance)
{
	// Use bool value to determine whether to play a sound this tick
	PlaySoundThisTick = Instance.GetValue().Get<bool>();
	if (PlaySoundThisTick)
	{
		LOG("Spacebar pressed");
	}
}
