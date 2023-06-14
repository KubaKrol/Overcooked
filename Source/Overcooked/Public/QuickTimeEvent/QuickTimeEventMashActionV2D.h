// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventMashActionV2D.generated.h"

class UEnhancedPlayerInput;
class UInputAction;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UQuickTimeEventMashActionV2D : public UQuickTimeEventAction
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
	FVector2D Vector;
	UPROPERTY()
	int MashCount;
	UPROPERTY()
	int CurrentMashCount;
	UPROPERTY()
	bool ButtonReleased;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* InputAction, FVector2D Vector, int MashCount, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
