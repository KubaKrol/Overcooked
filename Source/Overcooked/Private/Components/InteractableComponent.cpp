// Fill out your copyright notice in the Description page of Project Settings.


#include "Overcooked/Public/Player/PlayerCharacter.h"
#include "Overcooked/Public/Components/HolderComponent.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
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
	if (Toggle)
	{
		if (Toggled)
		{
			InteractionProgress += GetWorld()->DeltaTimeSeconds * GetInteractionSpeed();

			if (InteractionProgress >= 1.0f)
				InteractionFinished();
		}
	}

}

void UInteractableComponent::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanInteract(PlayerCharacter))
		return;

	if (Toggle)
	{
		Toggled = !Toggled;
		return;
	}

	InteractionProgress += GetWorld()->DeltaTimeSeconds * GetInteractionSpeed();

	if (InteractionProgress >= 1.0f)
		InteractionFinished();
}

bool UInteractableComponent::CanInteract(APlayerCharacter* PlayerCharacter) const
{
	bool canInteract = true;

	if (PlayerMushHaveHoldable)
	{
		if (PlayerCharacter->GetHolderComponent()->IsHolding())
		{
			if (PlayerCharacter->GetHolderComponent()->GetHoldable()->GetHoldableName() == PlayerHoldableName)
			{
				canInteract = true;
			}
			else
			{
				canInteract = false;
				return canInteract;
			}
		}
		else 
		{
			canInteract = false;
			return canInteract;
		}
	}

	if (MustHaveHoldable)
	{
		UHolderComponent* MyHolderComponent = Cast<UHolderComponent>(GetOwner()->GetComponentByClass(UHolderComponent::StaticClass()));

		if (!MyHolderComponent) 
		{
			UE_LOG(LogTemp, Error, TEXT("Interactable component must hold holdable to interact but does not have Holder Component! Fix it!"));
			return false;
		}
		else
		{
			if (MyHolderComponent->IsHolding())
			{
				if (MyHolderComponent->GetHoldable()->GetHoldableName() == HoldableName)
				{
					canInteract = true;
				}
				else 
				{
					canInteract = false;
					return canInteract;
				}
			}
			else
			{
				canInteract = false;
				return canInteract;
			}
		}

	}

	return canInteract;
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
	if (Toggle)
		Toggled = false;

	OnInteractionFinished.Broadcast();

	InteractionProgress = 0.0f;
}

