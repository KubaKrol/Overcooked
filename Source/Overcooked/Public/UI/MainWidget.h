// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:
	UPROPERTY(EditAnywhere)
	TArray<UNamedSlot*> ClientCardsSlots;

private:

#pragma endregion

#pragma region Methods

public:
	UFUNCTION(BlueprintCallable)
	void SetClientCardsSlots(TArray<UNamedSlot*> Slots);

	UFUNCTION(BlueprintCallable)
	TArray<UNamedSlot*> GetClientCardsSlots();

protected:

private:

#pragma endregion
	
};
