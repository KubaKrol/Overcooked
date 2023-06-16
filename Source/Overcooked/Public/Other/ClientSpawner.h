// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClientSpawner.generated.h"

class AClient;

UCLASS()
class OVERCOOKED_API AClientSpawner : public AActor
{
	GENERATED_BODY()
	
#pragma region Variables

public:
	UPROPERTY(EditAnywhere)
	int MaxClients = 6;

	UPROPERTY(EditAnywhere)
	float SpawningInterval = 10.0f;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AClient>> ClientsList;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawningLocationActors;

	UPROPERTY(EditAnywhere)
	int CurrentSpawnLocationIndex = 0;

protected:

private:
	UPROPERTY()
	float Timer = 0.0f;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this actor's properties
	AClientSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AClient* SpawnClient();

#pragma endregion

};
