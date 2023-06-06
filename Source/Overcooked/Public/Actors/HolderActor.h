// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "HolderActor.generated.h"

class IHoldable;
class IInteractable;
class AItem;

UCLASS()
class OVERCOOKED_API AHolderActor : public AActor, public IHolder
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HoldLocation;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IHoldable> MyHoldable;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> ItemToSpawn;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this actor's properties
	AHolderActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//IHolder interface
	virtual void ReceiveHoldable(IHoldable* Holdable) override;
	virtual bool IsHolding() const override;
	virtual IHoldable* GetHoldable() const override;
	virtual IHoldable* RemoveHoldable() override;
	virtual USceneComponent* GetHoldingSceneComponent() override;

	virtual void SpawnItem(TSubclassOf<AItem> Item);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

#pragma endregion
};
