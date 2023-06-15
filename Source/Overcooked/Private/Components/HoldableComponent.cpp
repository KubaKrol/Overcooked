// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HoldableComponent.h"
#include "Overcooked/Public/Interfaces/Holder.h"

// Sets default values for this component's properties
UHoldableComponent::UHoldableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoldableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHoldableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UHoldableComponent::GetHoldableName() const
{
	return HoldableName;
}

void UHoldableComponent::SetHolder(IHolder* Holder)
{
	if (Holder == nullptr)
	{
		MyHolder.SetInterface(nullptr);
		MyHolder.SetObject(nullptr);
		return;
	}

	CurrentState = EHoldableState::HELD;
	MyHolder.SetInterface(Holder);
	MyHolder.SetObject(Holder->_getUObject());
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetSimulatePhysics(false);
	GetOwner()->SetActorLocation(MyHolder->GetHoldingSceneComponent()->GetComponentLocation());
	GetOwner()->AttachToComponent(MyHolder->GetHoldingSceneComponent(), FAttachmentTransformRules::KeepWorldTransform);
}

IHolder* UHoldableComponent::GetHolder() const
{
	return MyHolder.GetInterface();
}

void UHoldableComponent::Throw(FVector direction)
{
	CurrentState = EHoldableState::THROWN;
	SetHolder(nullptr);
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetSimulatePhysics(true);
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetAllPhysicsLinearVelocity(FVector::Zero());
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddImpulse(direction * ThrowForce);
}

EHoldableState UHoldableComponent::GetCurrentState() const
{
	return CurrentState;
}

