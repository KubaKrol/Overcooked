// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HolderComponent.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/Actors/Item.h"
#include "Overcooked/Public/Components/HoldLocation.h"
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

	// ...

	if (ItemToSpawn)
		SpawnItem(ItemToSpawn);
}


// Called every frame
void UHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHolderComponent::ReceiveHoldable(IHoldable* Holdable)
{
	if (IsHolding())
		return;

	MyHoldable.SetInterface(Holdable);
	MyHoldable.SetObject(Holdable->_getUObject());
	MyHoldable->SetHolder(this);
}

bool UHolderComponent::IsHolding() const
{
	if (MyHoldable != nullptr)
		return true;

	return false;
}

IHoldable* UHolderComponent::GetHoldable() const
{
	return MyHoldable.GetInterface();
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
	if (HoldLocation == nullptr)
		HoldLocation = Cast<UHoldLocation>(GetOwner()->GetComponentByClass(UHoldLocation::StaticClass()));

	if (HoldLocation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Holder does not have HoldLocation component!"))
		check(false);
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

