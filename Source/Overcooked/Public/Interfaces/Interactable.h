// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APlayerCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class OVERCOOKED_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(APlayerCharacter* PlayerCharacter);
	virtual bool CanInteract(APlayerCharacter* PlayerCharacter) const;
	virtual float GetInteractionSpeed() const;
	virtual float GetInteractionProgress() const;
	virtual void InteractionFinished();
};
