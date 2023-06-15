// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClientData.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UClientData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString WasherHoldableName = "Shampoo";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ChairHoldableName = "Scrissors";
};