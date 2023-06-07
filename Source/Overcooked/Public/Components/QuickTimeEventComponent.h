// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuickTimeEventComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERCOOKED_API UQuickTimeEventComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:

private:

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this component's properties
	UQuickTimeEventComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion		
};