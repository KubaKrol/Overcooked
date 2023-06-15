// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/QuickTimeEvent.h"

// Add default functionality here for any IQuickTimeEvent functions that are not pure virtual.

void IQuickTimeEvent::Initialize(APlayerCharacter* playerCharacter)
{
}

bool IQuickTimeEvent::CanInitialize(APlayerCharacter* playerCharacter) const
{
	return false;
}

bool IQuickTimeEvent::IsRunning() const
{
	return false;
}

float IQuickTimeEvent::GetProgress() const
{
	return 0.0f;
}

void IQuickTimeEvent::Finish()
{
}
