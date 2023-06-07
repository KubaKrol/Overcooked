// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "HoldableComponent.generated.h"

class IHolder;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERCOOKED_API UHoldableComponent : public UActorComponent, public IHoldable
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IHolder> MyHolder;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this component's properties
	UHoldableComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetHolder(IHolder* Holder) override;
	virtual IHolder* GetHolder() const override;
	virtual void Throw(FVector direction, float Force) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion
		
};
