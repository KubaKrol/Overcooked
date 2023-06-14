// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventMashAction.generated.h"

class UEnhancedPlayerInput;
class UInputAction;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UQuickTimeEventMashAction : public UQuickTimeEventAction
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
	int MashCount;
	UPROPERTY()
	int CurrentMashCount;
	UPROPERTY()
	bool ButtonReleased;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* InputAction, int MashCount, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
