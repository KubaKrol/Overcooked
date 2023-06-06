// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HolderActor.h"
#include "Actors/Item.h"

// Sets default values
AHolderActor::AHolderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	HoldLocation = CreateDefaultSubobject<USceneComponent>(TEXT("HoldLocation"));
	HoldLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHolderActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemToSpawn)
		SpawnItem(ItemToSpawn);
}

// Called every frame
void AHolderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHolderActor::ReceiveHoldable(IHoldable* Holdable)
{
	if (IsHolding())
		return;

	MyHoldable.SetInterface(Holdable);
	MyHoldable.SetObject(Holdable->_getUObject());
	MyHoldable->SetHolder(this);
}

bool AHolderActor::IsHolding() const
{
	UE_LOG(LogTemp, Warning, TEXT("Checking holder actor is holding"));

	if (MyHoldable != nullptr)
		return true;

	UE_LOG(LogTemp, Warning, TEXT("Holder actor is not holding"));

	return false;
}

IHoldable* AHolderActor::GetHoldable() const
{
	return MyHoldable.GetInterface();
}

IHoldable* AHolderActor::RemoveHoldable()
{
	IHoldable* holdable = MyHoldable.GetInterface();
	MyHoldable.SetInterface(nullptr);
	MyHoldable.SetObject(nullptr);
	return holdable;
}

USceneComponent* AHolderActor::GetHoldingSceneComponent()
{
	return HoldLocation;
}

void AHolderActor::SpawnItem(TSubclassOf<AItem> Item)
{
	AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemToSpawn, HoldLocation->GetComponentLocation(), HoldLocation->GetComponentRotation());
	if (NewItem)
		ReceiveHoldable(NewItem);
}

