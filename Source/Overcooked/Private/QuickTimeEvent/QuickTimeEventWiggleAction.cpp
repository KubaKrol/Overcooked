// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventWiggleAction.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventWiggleAction::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, int wiggleCount, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	WiggleCount = wiggleCount;
	Name = name;
	CurrentWiggleCount = 0;
	PreviousInputValue = FVector2D::Zero();
}

bool UQuickTimeEventWiggleAction::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);
	FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.IsZero())
		return false;

	if (FVector2D::Distance(Value, PreviousInputValue) > 1.0f)
	{
		CurrentWiggleCount++;
		PreviousInputValue = Value;

		if (!Finished && CurrentWiggleCount == WiggleCount)
		{
			Finish();
			return true;
		}
	}

	return false;
}

float UQuickTimeEventWiggleAction::GetProgress()
{
	return (float)CurrentWiggleCount / (float)WiggleCount;
}
