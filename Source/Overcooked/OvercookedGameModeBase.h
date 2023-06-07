// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OvercookedGameModeBase.generated.h"

class APlayerCharacter;

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
	TSubclassOf<APlayerCharacter> PlayerCharacterBlueprint;

protected:

private:

#pragma endregion

#pragma region Methods

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

#pragma endregion
};
