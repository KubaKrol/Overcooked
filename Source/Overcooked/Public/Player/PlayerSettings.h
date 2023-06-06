// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerSettings.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UPlayerSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementAcceleration = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RotationSpeed = 10.0f;
	
};
