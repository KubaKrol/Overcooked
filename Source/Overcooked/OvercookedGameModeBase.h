// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OvercookedGameModeBase.generated.h"

class APlayerCharacter;
class UClientManager;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API AOvercookedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Variables

public:
	UPROPERTY(EditAnywhere)
	int AmountOfPlayers = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerCharacter> PlayerCharacterBlueprint;

protected:
	UPROPERTY(VisibleAnywhere)
	UClientManager* ClientManager;

private:

#pragma endregion

#pragma region Methods

public:
	UFUNCTION(BlueprintCallable)
	UClientManager* GetClientManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	virtual void SpawnPlayers();

#pragma endregion
};
