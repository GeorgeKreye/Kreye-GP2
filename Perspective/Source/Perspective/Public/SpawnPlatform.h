// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPlatform.generated.h"

UCLASS()
class PERSPECTIVE_API ASpawnPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPlatform();

	UPROPERTY(VisibleAnywhere);
	/**
	 * @brief The mesh used by this object
	 */
	UStaticMeshComponent* StaticMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
