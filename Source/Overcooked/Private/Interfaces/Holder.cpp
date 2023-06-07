// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Holder.h"

// Add default functionality here for any IHolder functions that are not pure virtual.

void IHolder::ReceiveHoldable(IHoldable* Holdable)
{
}

bool IHolder::IsHolding() const
{
	return false;
}

IHoldable* IHolder::GetHoldable() const
{
	return nullptr;
}

IHoldable* IHolder::RemoveHoldable()
{
	return nullptr;
}

USceneComponent* IHolder::GetHoldingSceneComponent()
{
	return nullptr;
}

void IHolder::SpawnItem(TSubclassOf<AItem> Item)
{
}
