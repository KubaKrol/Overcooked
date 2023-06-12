// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventPressAction.generated.h"

class UEnhancedPlayerInput;
class UInputAction;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class OVERCOOKED_API UQuickTimeEventPressAction : public UQuickTimeEventAction
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:

private:
	UPROPERTY()
	UEnhancedPlayerInput* PlayerInput;
	UPROPERTY()
	UInputAction* InputAction;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* InputAction, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
