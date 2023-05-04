// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lab08ImpactSoundActor.generated.h"

UCLASS()
class KREYE_GP2_API ALab08ImpactSoundActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALab08ImpactSoundActor();

	// The mesh used by this actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	// The audio component used for playing impact SFX
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	TObjectPtr<UAudioComponent> Sound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when actor collides with something
	UFUNCTION()
	void OnImpactHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit);

private:
	// Determines whether to play the impact SFX this tick
	bool PlaySoundThisTick;
};
