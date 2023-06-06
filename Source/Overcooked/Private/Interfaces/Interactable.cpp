// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Interact()
{
}

bool IInteractable::CanInteract() const
{
	return false;
}

float IInteractable::GetInteractionSpeed() const
{
	return 0.0f;
}

float IInteractable::GetInteractionProgress() const
{
	return 0.0f;
}

void IInteractable::InteractionFinished()
{
}
