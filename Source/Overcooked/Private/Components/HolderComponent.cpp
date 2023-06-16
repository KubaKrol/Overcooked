// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HolderComponent.h"
#include "Components/BoxComponent.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/Components/HoldableComponent.h"
#include "Overcooked/Public/Actors/Item.h"
#include "Overcooked/Public/Components/HoldLocation.h"
#include "Overcooked/Public/Player/PlayerCharacter.h"
#include "Overcooked/Public/Actors/Client.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UHolderComponent::UHolderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHolderComponent::BeginPlay()
{
	Super::BeginPlay();

	//This is invoked just to print out error message if this component does not have HoldLocation specified.
	GetHoldingSceneComponent();

	if (ItemToSpawn)
		SpawnItem(ItemToSpawn);
}


// Called every frame
void UHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CatchCooldown -= GetWorld()->DeltaTimeSeconds;

	if (TryCatchHoldable)
		TryCatchItem(Cast<UBoxComponent>(CatchingBoxComponentReference.GetComponent(GetOwner())));
}

bool UHolderComponent::CanReceiveHoldable(IHoldable* Holdable) const
{
	if (IsHolding())
		return false;

	if (AcceptOnlySpecificHoldable)
	{
		if (Holdable->GetHoldableName() != AcceptableHoldableName)
			return false;
	}

	if (CheckForClientTask) 
	{
		UActorComponent* ActorComponent = Cast<UActorComponent>(Holdable);
		AClient* Client = Cast<AClient>(ActorComponent->GetOwner());

		if (Client == nullptr)
			return false;

		if (Client->GetCurrentClientTask() != ClientTask)
			return false;
	}

	return true;
}

void UHolderComponent::ReceiveHoldable(IHoldable* Holdable)
{
	if (!CanReceiveHoldable(Holdable))
		return;

	MyHoldable.SetInterface(Holdable);
	MyHoldable.SetObject(Holdable->_getUObject());
	MyHoldable->SetHolder(this);
	OnHoldableReceived();
}

void UHolderComponent::OnHoldableReceived()
{
	OnHoldableReceivedDelegate.Broadcast(Cast<UHoldableComponent>(MyHoldable.GetInterface()));
}

bool UHolderComponent::IsHolding() const
{
	if (MyHoldable != nullptr)
		return true;

	return false;
}

bool UHolderComponent::CanHoldableBeTaken() const
{
	return HoldableCanByTaken;
}

IHoldable* UHolderComponent::GetHoldable() const
{
	return MyHoldable.GetInterface();
}

UHoldableComponent* UHolderComponent::GetHoldableComponent() const
{
	if (!IsHolding())
		return nullptr;

	return Cast<UHoldableComponent>(MyHoldable.GetInterface());
}

IHoldable* UHolderComponent::RemoveHoldable()
{
	IHoldable* holdable = MyHoldable.GetInterface();
	MyHoldable.SetInterface(nullptr);
	MyHoldable.SetObject(nullptr);
	return holdable;
}

USceneComponent* UHolderComponent::GetHoldingSceneComponent()
{
	UHoldLocation* HoldLocation = Cast<UHoldLocation>(HoldLocationReference.GetComponent(GetOwner()));

	if (HoldLocation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Holder does not have HoldLocation component!"))
	}

	return HoldLocation;
}

void UHolderComponent::SpawnItem(TSubclassOf<AItem> Item)
{
	AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemToSpawn, GetHoldingSceneComponent()->GetComponentLocation(), GetHoldingSceneComponent()->GetComponentRotation());

	if (NewItem)
	{
		TArray<UActorComponent*> Holdables = NewItem->GetComponentsByInterface(UHoldable::StaticClass());

		if(Holdables.Num() > 1)
			UE_LOG(LogTemp, Warning, TEXT("Spawned item has more than one holdable components!"))

		if(Holdables.Num() <= 0)
			UE_LOG(LogTemp, Warning, TEXT("Spawned item does not have holdable component!"))

		for (int i = 0; i < Holdables.Num(); i++)
		{
			ReceiveHoldable(Cast<IHoldable>(Holdables[i]));
			return;
		}
	}
}

void UHolderComponent::TryCatchItem(UPrimitiveComponent* CatchingCollider)
{
	if (CatchingCollider == nullptr)
		return;

	if (CatchCooldown > 0.0f)
		return;

	TArray<AActor*> OverlappingActors;
	CatchingCollider->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor == GetOwner())
			continue;

		TArray<UActorComponent*> Holdables = OverlappingActor->GetComponentsByInterface(UHoldable::StaticClass());

		for (int i = 0; i < Holdables.Num(); i++)
		{
			IHoldable* Holdable = Cast<IHoldable>(Holdables[i]);
			if (Holdable)
			{
				if (Holdable->GetCurrentState() == EHoldableState::THROWN)
				{
					ReceiveHoldable(Holdable);
					return;
				}
			}
		}
	}
}

void UHolderComponent::SetCatchCooldown(float CooldownTime)
{
	CatchCooldown = CooldownTime;
}

