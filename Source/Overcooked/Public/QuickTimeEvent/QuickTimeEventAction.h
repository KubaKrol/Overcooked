// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuickTimeEventAction.generated.h"

class UInputAction;

UENUM(BlueprintType)
enum class EQuickTimeEventTriggerType : uint8 {
	QTE_Press      UMETA(DisplayName = "Press"),
	QTE_Hold       UMETA(DisplayName = "Hold")
};

USTRUCT(BlueprintType)
struct FQuickTimeEventActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EQuickTimeEventTriggerType TriggerType;
	UPROPERTY(EditAnywhere)
	UInputAction* InputAction;
};

/**
 * 
 */
UCLASS(BlueprintType)
class OVERCOOKED_API UQuickTimeEventAction : public UObject
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:

#pragma endregion

#pragma region Methods

public:

protected:

private:

#pragma endregion
};
