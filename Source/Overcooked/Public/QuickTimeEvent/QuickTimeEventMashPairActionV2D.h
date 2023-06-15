// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventMashPairActionV2D.generated.h"

class UEnhancedPlayerInput;
class UInputAction;
class PreviousAction;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UQuickTimeEventMashPairActionV2D : public UQuickTimeEventAction
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:
	UPROPERTY()
	UEnhancedPlayerInput* PlayerInput;
	UPROPERTY()
	UInputAction* FirstInputAction;
	UPROPERTY()
	UInputAction* SecondInputAction;
	UPROPERTY()
	int MashCount;
	UPROPERTY()
	int CurrentMashCount;
	UPROPERTY()
	int PreviousAction;

#pragma endregion

#pragma region Methods

public:
	void Init(UEnhancedPlayerInput* PlayerInput, UInputAction* FirstInputAction, UInputAction* SecondInputAction, int MashCount, FString Name);
	virtual bool CheckInput() override;
	virtual float GetProgress() override;

protected:

private:

#pragma endregion
};
