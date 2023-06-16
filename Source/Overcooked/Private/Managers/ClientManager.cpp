// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ClientManager.h"

AClient* UClientManager::SpawnClient(TSubclassOf<AClient> ClientBlueprint, FVector Location, FRotator Rotation)
{
	AClient* Client = Cast<AClient>(GetWorld()->SpawnActor(ClientBlueprint, &Location, &Rotation));
	ClientsList.Add(Client);
	return Client;
}

int UClientManager::GetCurrentClientsCount() const
{
	return ClientsList.Num();
}
