// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/Interfaces/Interactable.h"
#include "Item.generated.h"

UCLASS()
class OVERCOOKED_API AItem : public AActor, public IHoldable, public IInteractable
{
	GENERATED_BODY()
	
#pragma region Variables

public:

protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IHolder> MyHolder;

	UPROPERTY(VisibleAnywhere)
	float InteractionProgress;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//IHoldable interface
	virtual void SetHolder(IHolder* Holder) override;
	virtual IHolder* GetHolder() const override;
	virtual void Throw(FVector direction, float Force) override;

	//IInteractable interface
	virtual void Interact() override;
	virtual bool CanInteract() const override;
	virtual float GetInteractionSpeed() const override;
	UFUNCTION(BlueprintCallable)
	virtual float GetInteractionProgress() const override;
	virtual void InteractionFinished() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

#pragma endregion

};
