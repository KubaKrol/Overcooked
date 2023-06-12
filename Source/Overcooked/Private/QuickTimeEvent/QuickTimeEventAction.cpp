// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickTimeEvent/QuickTimeEventAction.h"

bool UQuickTimeEventAction::CheckInput()
{
	return false;
}

float UQuickTimeEventAction::GetProgress()
{
	return 0.0f;
}

FString UQuickTimeEventAction::GetName() const
{
	return Name;
}

void UQuickTimeEventAction::Finish()
{
	Finished = true;
}
