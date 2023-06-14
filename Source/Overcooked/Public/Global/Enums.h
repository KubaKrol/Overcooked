// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums.generated.h"

UCLASS()
class OVERCOOKED_API UEnums : public UObject
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EDirection : uint8
{
	NONE		UMETA(DisplayName = "Not specified"),
	IDLE		UMETA(DisplayName = "Idle"),
	UP			UMETA(DisplayName = "Up Direction"),
	RIGHT       UMETA(DisplayName = "Right Direction"),
	DOWN        UMETA(DisplayName = "Down Direction"),
	LEFT		UMETA(DisplayName = "Left Direction"),
};
