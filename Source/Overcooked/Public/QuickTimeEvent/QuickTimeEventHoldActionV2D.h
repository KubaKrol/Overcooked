// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventHoldActionV2D.generated.h"

class UEnhancedPlayerInput;
class UInputAction;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UQuickTimeEventHoldActionV2D : public UQuickTimeEventAction
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
	FVector2D Vector2D;
	UPROPERTY()
	float HoldTime;
	UPROPERTY()
	float HoldTimer;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* InputAction, FVector2D Vector, float HoldTime, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
