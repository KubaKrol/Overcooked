// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Overcooked/Public/UI/DefaultHUD.h"
#include "Managers/ClientManager.h"

AClient* UClientManager::SpawnClient(TSubclassOf<AClient> ClientBlueprint, FVector Location, FRotator Rotation)
{
	AClient* Client = Cast<AClient>(GetWorld()->SpawnActor(ClientBlueprint, &Location, &Rotation));
	ClientsList.Add(Client);
	AHUD* HUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
	ADefaultHUD* DefaultHUD = Cast<ADefaultHUD>(HUD);
	DefaultHUD->AddClientCard(Client);
	
	return Client;
}

int UClientManager::GetCurrentClientsCount() const
{
	return ClientsList.Num();
}

void UClientManager::RemoveClient(AClient* Client)
{
	if (ClientsList.Contains(Client))
		ClientsList.Remove(Client);
}
