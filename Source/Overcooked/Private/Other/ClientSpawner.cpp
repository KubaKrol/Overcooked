// Fill out your copyright notice in the Description page of Project Settings.


#include "Overcooked/OvercookedGameModeBase.h"
#include "Overcooked/Public/Managers/ClientManager.h"
#include "Overcooked/Public/Actors/Client.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Other/ClientSpawner.h"

// Sets default values
AClientSpawner::AClientSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClientSpawner::BeginPlay()
{
	Super::BeginPlay();
	Timer = SpawningInterval - 1.0f;
}

AClient* AClientSpawner::SpawnClient()
{
	UClientManager* ClientManager = Cast<AOvercookedGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetClientManager();

	if (ClientManager->GetCurrentClientsCount() >= MaxClients) 
	{
		CurrentSpawnLocationIndex = 0;
		return nullptr;
	}

	AClient* Client = ClientManager->SpawnClient(
		ClientsList[FMath::RandRange(0, ClientsList.Num() - 1)],
		SpawningLocationActors[CurrentSpawnLocationIndex]->GetActorLocation(),
		SpawningLocationActors[CurrentSpawnLocationIndex]->GetActorRotation());

	CurrentSpawnLocationIndex++;

	return Client;
}

// Called every frame
void AClientSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += GetWorld()->DeltaTimeSeconds;

	if (Timer > SpawningInterval)
	{
		SpawnClient();
		Timer = 0.0f;
	}
}

