// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "Overcooked/Public/Global/Enums.h"
#include "HolderComponent.generated.h"

class IHoldable;
class AItem;
class UHoldLocation;
class UHoldableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoldableReceived, UHoldableComponent*, Holdable);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERCOOKED_API UHolderComponent : public UActorComponent, public IHolder
{
	GENERATED_BODY()

#pragma region Variables

public:
	UPROPERTY(EditAnywhere)
	bool AcceptOnlySpecificHoldable;
	UPROPERTY(EditAnywhere)
	FString AcceptableHoldableName;
	UPROPERTY(EditAnywhere)
	bool CheckForClientTask;
	UPROPERTY(EditAnywhere)
	EClientTask ClientTask;
	UPROPERTY(EditAnywhere)
	bool HoldableCanByTaken = true;

protected:

private:
	UPROPERTY(BlueprintAssignable)
	FOnHoldableReceived OnHoldableReceivedDelegate;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IHoldable> MyHoldable;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> ItemToSpawn;

	UPROPERTY(EditAnywhere)
	FComponentReference HoldLocationReference;

	UPROPERTY(EditAnywhere)
	bool TryCatchHoldable;

	UPROPERTY(EditAnywhere)
	FComponentReference CatchingBoxComponentReference;;

	UPROPERTY()
	float CatchCooldown = 0.0f;

#pragma endregion

#pragma region Metehods

public:
	// Sets default values for this component's properties
	UHolderComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//IHolder Interface
	virtual bool CanReceiveHoldable(IHoldable* Holdable) const override;
	virtual void ReceiveHoldable(IHoldable* Holdable) override;
	virtual void OnHoldableReceived() override;
	virtual bool IsHolding() const override;
	virtual bool CanHoldableBeTaken() const override;
	virtual IHoldable* GetHoldable() const override;
	virtual IHoldable* RemoveHoldable() override;
	virtual USceneComponent* GetHoldingSceneComponent() override;
	virtual void SpawnItem(TSubclassOf<AItem> Item) override;
	virtual void TryCatchItem(UPrimitiveComponent* catchingCollider) override;
	virtual void SetCatchCooldown(float CooldownTime) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion
};
