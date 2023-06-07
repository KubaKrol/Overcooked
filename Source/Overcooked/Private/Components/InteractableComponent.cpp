// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractableComponent::Interact()
{
	if (!CanInteract())
		return;

	if (InteractionProgress >= 1.0f)
		return;

	InteractionProgress += GetWorld()->DeltaTimeSeconds * GetInteractionSpeed();

	if (InteractionProgress >= 1.0f)
		InteractionFinished();
}

bool UInteractableComponent::CanInteract() const
{
	return true;
}

float UInteractableComponent::GetInteractionSpeed() const
{
	return InteractionSpeed;
}

float UInteractableComponent::GetInteractionProgress() const
{
	return InteractionProgress;
}

void UInteractableComponent::InteractionFinished()
{
	OnInteractionFinished.Broadcast();
}

