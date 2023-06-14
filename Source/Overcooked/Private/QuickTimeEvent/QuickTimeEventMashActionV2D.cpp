// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventMashActionV2D.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventMashActionV2D::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, FVector2D vector, int mashCount, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	Vector = vector;
	MashCount = mashCount;
	Name = name;
	CurrentMashCount = 0;
}

bool UQuickTimeEventMashActionV2D::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);
	FVector2D Value = InputActionValue.Get<FVector2D>();

	if (FVector2D::Distance(Value, Vector) > 0.75f && !ButtonReleased)
		ButtonReleased = true;

	if (FVector2D::Distance(Value, Vector) < 0.35f && ButtonReleased)
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

float UQuickTimeEventMashActionV2D::GetProgress()
{
	return (float)CurrentMashCount / (float)MashCount;
}
