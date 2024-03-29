// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Holdable.h"

// Add default functionality here for any IHoldable functions that are not pure virtual.

FString IHoldable::GetHoldableName() const
{
	return FString();
}

void IHoldable::SetHolder(IHolder* Holder)
{
}

IHolder* IHoldable::GetHolder() const
{
	return nullptr;
}

void IHoldable::Throw(FVector direction)
{
}

EHoldableState IHoldable::GetCurrentState() const
{
	return EHoldableState::HELD;
}
