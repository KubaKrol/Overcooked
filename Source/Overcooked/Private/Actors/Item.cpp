// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Item.h"
#include "Overcooked/Public/Interfaces/Holder.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetHolder(IHolder* Holder)
{
	if (Holder == nullptr)
	{
		MyHolder.SetInterface(nullptr);
		MyHolder.SetObject(nullptr);
		return;
	}

	MyHolder.SetInterface(Holder);
	MyHolder.SetObject(Holder->_getUObject());
	Mesh->SetSimulatePhysics(false);
	SetActorLocation(MyHolder->GetHoldingSceneComponent()->GetComponentLocation());
	AttachToComponent(MyHolder->GetHoldingSceneComponent(), FAttachmentTransformRules::KeepWorldTransform);
}

IHolder* AItem::GetHolder() const
{
	return MyHolder.GetInterface();
}

void AItem::Throw(FVector direction, float Force)
{
	SetHolder(nullptr);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Mesh->SetSimulatePhysics(true);
	Mesh->AddImpulse(direction * Force);
}

void AItem::Interact()
{
	if (!CanInteract())
		return;

	if (InteractionProgress >= 1.0f)
		return;

	InteractionProgress += GetWorld()->DeltaTimeSeconds * GetInteractionSpeed();

	if (InteractionProgress >= 1.0f)
		InteractionFinished();
}

bool AItem::CanInteract() const
{
	return true;
}

float AItem::GetInteractionSpeed() const
{
	return 0.5f;
}

float AItem::GetInteractionProgress() const
{
	return InteractionProgress;
}

void AItem::InteractionFinished()
{
	OnInteractionFinished();
}

