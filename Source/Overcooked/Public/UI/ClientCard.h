// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClientCard.generated.h"

class AClient;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API UClientCard : public UUserWidget
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere)
	AClient* MyClient;

#pragma endregion

#pragma region Methods

public:
	void Init(AClient* Client);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialize();

	UFUNCTION(BlueprintCallable)
	AClient* GetClient() const;

protected:

private:

#pragma endregion

};
