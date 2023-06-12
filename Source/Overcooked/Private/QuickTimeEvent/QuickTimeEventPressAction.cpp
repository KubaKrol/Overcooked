// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventPressAction.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventPressAction::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	Name = name;
}

bool UQuickTimeEventPressAction::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);

	if (InputActionValue.Get<bool>() == true)
	{
		if (!Finished)
			Finish();

		return true;
	}

	return false;
}

float UQuickTimeEventPressAction::GetProgress()
{
	if (Finished)
		return 1.0f;

	return 0.0f;
}
