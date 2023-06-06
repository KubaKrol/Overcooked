// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPrimaryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSecondaryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputThrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputDash;
};
