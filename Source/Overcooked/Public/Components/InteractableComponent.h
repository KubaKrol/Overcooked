// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Overcooked/Public/Interfaces/Interactable.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERCOOKED_API UInteractableComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

#pragma region Variables

public:
	
protected:

private:
	UPROPERTY(EditDefaultsOnly)
	float InteractionSpeed = 0.5f;

	UPROPERTY(VisibleAnywhere)
	float InteractionProgress;

	UPROPERTY(BlueprintAssignable)
	FOnInteractionFinished OnInteractionFinished;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this component's properties
	UInteractableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact() override;
	virtual bool CanInteract() const override;
	virtual float GetInteractionSpeed() const override;
	UFUNCTION(BlueprintCallable)
	virtual float GetInteractionProgress() const override;
	virtual void InteractionFinished() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion	
};
