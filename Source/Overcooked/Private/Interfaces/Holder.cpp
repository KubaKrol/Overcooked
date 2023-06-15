// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Holder.h"

// Add default functionality here for any IHolder functions that are not pure virtual.

bool IHolder::CanReceiveHoldable(IHoldable* Holdable) const
{
	return false;
}

void IHolder::ReceiveHoldable(IHoldable* Holdable)
{
}

void IHolder::OnHoldableReceived()
{
}

bool IHolder::IsHolding() const
{
	return false;
}

bool IHolder::CanHoldableBeTaken() const
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

void IHolder::TryCatchItem(UPrimitiveComponent* catchingCollider)
{
}

void IHolder::SetCatchCooldown(float CooldownTime)
{
}
