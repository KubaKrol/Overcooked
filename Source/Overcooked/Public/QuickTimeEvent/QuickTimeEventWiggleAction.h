// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventWiggleAction.generated.h"

class UEnhancedPlayerInput;
class UInputAction;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UQuickTimeEventWiggleAction : public UQuickTimeEventAction
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
	UPROPERTY()
	int WiggleCount;
	UPROPERTY()
	int CurrentWiggleCount;
	UPROPERTY()
	FVector2D PreviousInputValue;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* InputAction, int WiggleCount, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
