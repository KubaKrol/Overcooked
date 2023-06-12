// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuickTimeEventAction.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class OVERCOOKED_API UQuickTimeEventAction : public UObject
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:
	UPROPERTY()
	bool Finished;

	UPROPERTY()
	FString Name;

private:

#pragma endregion

#pragma region Methods

public:
	virtual bool CheckInput();
	virtual float GetProgress();
	virtual FString GetName() const;

protected:
	virtual void Finish();

private:

#pragma endregion
};
