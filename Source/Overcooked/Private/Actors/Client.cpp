// Fill out your copyright notice in the Description page of Project Settings.


#include "Overcooked/Public/Components/HoldableComponent.h"
#include "Overcooked/Public/Data/ClientData.h"
#include "Actors/Client.h"

// Sets default values
AClient::AClient()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	HoldableComponent = CreateDefaultSubobject<UHoldableComponent>(TEXT("Holdable"));
}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AClient::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UClientData* AClient::GetClientData() const
{
	return ClientData;
}

EClientTask AClient::GetCurrentClientTask() const
{
	return GetClientData()->ClientTaskSequence[CurrentTaskIndex];
}

void AClient::IncrementClientTaskIndex()
{
	if (CurrentTaskIndex + 1 == GetClientData()->ClientTaskSequence.Num())
		return;

	CurrentTaskIndex++;
}

