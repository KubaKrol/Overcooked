// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Overcooked/Public/Global/Enums.h"
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
	float PatienceTime = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString WasherHoldableName = "Shampoo";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ChairHoldableName = "Scrissors";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<EClientTask> ClientTaskSequence;
};
