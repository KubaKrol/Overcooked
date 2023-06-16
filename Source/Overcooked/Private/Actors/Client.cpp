// Fill out your copyright notice in the Description page of Project Settings.


#include "Overcooked/OvercookedGameModeBase.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "Overcooked/Public/Components/HoldableComponent.h"
#include "Overcooked/Public/Data/ClientData.h"
#include "Overcooked/Public/Managers/ClientManager.h"
#include "Overcooked/Public/UI/DefaultHUD.h"
#include "Kismet/GameplayStatics.h"
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

	Patience += GetWorld()->DeltaTimeSeconds;

	if (Patience >= GetClientData()->PatienceTime)
		Disable();
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

float AClient::GetPatience() const
{
	return Patience / GetClientData()->PatienceTime;
}

void AClient::IncrementClientTaskIndex()
{
	if (CurrentTaskIndex + 1 == GetClientData()->ClientTaskSequence.Num())
		return;

	CurrentTaskIndex++;

	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CurrentTaskIndex);
}

void AClient::Disable()
{
	if (HoldableComponent->GetHolder() != nullptr)
		HoldableComponent->GetHolder()->RemoveHoldable();

	Cast<AOvercookedGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetClientManager()->RemoveClient(this);
	Cast<ADefaultHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->RemoveClientCard(this);
	Destroy();
}

