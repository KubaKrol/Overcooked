// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Holder.generated.h"

class IHoldable;
class AItem;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHolder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OVERCOOKED_API IHolder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanReceiveHoldable(IHoldable* Holdable) const;
	virtual void ReceiveHoldable(IHoldable* Holdable);
	virtual void OnHoldableReceived();
	virtual bool IsHolding() const;
	virtual bool CanHoldableBeTaken() const;
	virtual IHoldable* GetHoldable() const;
	virtual IHoldable* RemoveHoldable();
	virtual USceneComponent* GetHoldingSceneComponent();
	virtual void SpawnItem(TSubclassOf<AItem> Item);
	virtual void TryCatchItem(UPrimitiveComponent* catchingCollider);
	virtual void SetCatchCooldown(float CooldownTime);
};
