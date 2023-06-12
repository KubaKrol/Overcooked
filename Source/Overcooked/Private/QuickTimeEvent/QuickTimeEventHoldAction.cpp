// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventHoldAction.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventHoldAction::Init(UEnhancedPlayerInput* playerInput, UInputAction* inputAction, float holdTime, FString name)
{
	PlayerInput = playerInput;
	InputAction = inputAction;
	Name = name;
	HoldTime = holdTime;
	HoldTimer = 0;
}

bool UQuickTimeEventHoldAction::CheckInput()
{
	FInputActionValue InputActionValue = PlayerInput->GetActionValue(InputAction);
	UE_LOG(LogTemp, Warning, TEXT("Hold action is %s"), *InputActionValue.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Hold timer is: %f"), HoldTimer);

	if (InputActionValue.Get<bool>() == true)
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

float UQuickTimeEventHoldAction::GetProgress()
{
	return HoldTimer / HoldTime;
}
