// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClientManager.generated.h"

class AClient;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UClientManager : public UObject
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AClient*> ClientsList;

#pragma endregion

#pragma region Methods

public:
	UFUNCTION(BlueprintCallable)
	AClient* SpawnClient(TSubclassOf<AClient> ClientBlueprint, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	int GetCurrentClientsCount() const;

	void RemoveClient(AClient* Client);

protected:

private:

#pragma endregion

};
