// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Lab08SoundPawn.generated.h"

UCLASS()
class KREYE_GP2_API ALab08SoundPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALab08SoundPawn();

	// The mesh used by this pawn
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	// The audio component used to play sound
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Sound)
	TObjectPtr<UAudioComponent> Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
