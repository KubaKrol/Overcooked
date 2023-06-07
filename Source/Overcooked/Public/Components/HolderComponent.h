// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "HolderComponent.generated.h"

class IHoldable;
class AItem;
class UHoldLocation;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERCOOKED_API UHolderComponent : public UActorComponent, public IHolder
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IHoldable> MyHoldable;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> ItemToSpawn;

	UPROPERTY(VisibleAnywhere)
	UHoldLocation* HoldLocation;

#pragma endregion

#pragma region Metehods

public:
	// Sets default values for this component's properties
	UHolderComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ReceiveHoldable(IHoldable* Holdable) override;
	virtual bool IsHolding() const override;
	virtual IHoldable* GetHoldable() const override;
	virtual IHoldable* RemoveHoldable() override;
	virtual USceneComponent* GetHoldingSceneComponent() override;
	virtual void SpawnItem(TSubclassOf<AItem> Item) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion
};
