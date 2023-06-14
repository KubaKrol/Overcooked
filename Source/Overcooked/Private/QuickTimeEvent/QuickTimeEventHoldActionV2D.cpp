// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventHoldActionV2D.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventHoldActionV2D::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, FVector2D vector, float holdTime, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	Vector2D = vector;
	Name = name;
	HoldTime = holdTime;
	HoldTimer = 0;
}

bool UQuickTimeEventHoldActionV2D::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);
	FVector2D Value = InputActionValue.Get<FVector2D>();

	if(FVector2D::Distance(Value, Vector2D) < 0.35f)
	{
		HoldTimer += GetWorld()->DeltaTimeSeconds;

		if (HoldTimer > HoldTime)
		{
			if (!Finished)
				Finish();

			return true;
		}
	}

	return false;
}

float UQuickTimeEventHoldActionV2D::GetProgress()
{
	return HoldTimer / HoldTime;
}
