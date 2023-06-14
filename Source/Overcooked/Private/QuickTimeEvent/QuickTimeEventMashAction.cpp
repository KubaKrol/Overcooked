// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventMashAction.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventMashAction::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, int mashCount, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	MashCount = mashCount;
	Name = name;
	CurrentMashCount = 0;
}

bool UQuickTimeEventMashAction::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);

	if (InputActionValue.Get<bool>() == false && !ButtonReleased)
		ButtonReleased = true;

	if (InputActionValue.Get<bool>() == true && ButtonReleased)
	{
		ButtonReleased = false;
		CurrentMashCount++;

		if (!Finished && CurrentMashCount == MashCount)
		{
			Finish();
			return true;
		}
	}

	return false;
}

float UQuickTimeEventMashAction::GetProgress()
{
	return (float)CurrentMashCount / (float)MashCount;
}
