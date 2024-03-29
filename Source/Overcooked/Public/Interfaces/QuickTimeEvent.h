// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickTimeEvent.generated.h"

class APlayerCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuickTimeEvent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OVERCOOKED_API IQuickTimeEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Initialize(APlayerCharacter* playerCharacter);
	virtual bool CanInitialize(APlayerCharacter* playerCharacter) const;
	virtual bool IsRunning() const;
	virtual float GetProgress() const;
	virtual void Finish();
};
