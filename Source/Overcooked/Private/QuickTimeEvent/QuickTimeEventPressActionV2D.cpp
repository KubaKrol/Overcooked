// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventPressActionV2D.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventPressActionV2D::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, FVector2D vector, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	Vector2D = vector;
	Name = name;
}

bool UQuickTimeEventPressActionV2D::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);
	FVector2D Value = InputActionValue.Get<FVector2D>();

	if (FVector2D::Distance(Value, Vector2D) < 0.35f)
	{
		if (!Finished)
			Finish();

		return true;
	}

	return false;
}

float UQuickTimeEventPressActionV2D::GetProgress()
{
	if (Finished)
		return 1.0f;

	return 0.0f;
}
