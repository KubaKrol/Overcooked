// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputConfigData;
class UPlayerSettings;
class AItem;
class AHolderActor;
class UBoxComponent;
class IHoldable;
class IInteractable;

UCLASS()
class OVERCOOKED_API APlayerCharacter : public ACharacter, public IHolder
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputConfigData* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings")
	UPlayerSettings* PlayerSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Handling", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HoldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Handling", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IHoldable> MyHoldable;

private:

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//IHolder interface
	virtual void ReceiveHoldable(IHoldable* Holdable) override;
	virtual bool IsHolding() const override;
	virtual IHoldable* GetHoldable() const override;
	virtual IHoldable* RemoveHoldable() override;
	virtual USceneComponent* GetHoldingSceneComponent() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Handle move input
	void Move(const FInputActionValue& Value);

	void PrimaryAction();
	void SecondaryAction();
	void Dash();
	void Throw();

#pragma endregion
};
