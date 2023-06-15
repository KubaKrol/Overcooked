// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventMashPairAction.h"
#include "EnhancedPlayerInput.h"

void UQuickTimeEventMashPairAction::Init(UEnhancedPlayerInput* playerInput, UInputAction* firstInputAction, UInputAction* secondInputAction, int mashCount, FString name)
{
	PlayerInput = playerInput;
	FirstInputAction = firstInputAction;
	SecondInputAction = secondInputAction;
	MashCount = mashCount;
	Name = name;
	CurrentMashCount = 0;
	PreviousAction = 0;
}

bool UQuickTimeEventMashPairAction::CheckInput()
{
	if (Finished)
		return true;

	FInputActionValue FirstInputActionValue = PlayerInput->GetActionValue(FirstInputAction);
	FInputActionValue SecondInputActionValue = PlayerInput->GetActionValue(SecondInputAction);

	if (FirstInputActionValue.Get<bool>() == true)
	{
		if (PreviousAction == 2 || PreviousAction == 0)
		{
			CurrentMashCount++;
			PreviousAction = 1;

			if (!Finished && CurrentMashCount == MashCount)
			{
				Finish();
				return true;
			}
			else 
				return false;
		}
	}

	if (SecondInputActionValue.Get<bool>() == true)
	{
		if (PreviousAction == 1 || PreviousAction == 0)
		{
			CurrentMashCount++;
			PreviousAction = 2;

			if (!Finished && CurrentMashCount == MashCount)
			{
				Finish();
				return true;
			}
			else
				return false;
		}
	}

	return false;
}

float UQuickTimeEventMashPairAction::GetProgress()
{
	return (float)CurrentMashCount / (float)MashCount;
}
