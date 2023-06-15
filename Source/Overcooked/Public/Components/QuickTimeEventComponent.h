// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Overcooked/Public/Interfaces/QuickTimeEvent.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventAction.h"
#include "QuickTimeEventComponent.generated.h"

class UEnhancedPlayerInput;
class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitialize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitializeWithHoldable, FString, HoldableName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionFinished, int, ActionIndex);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OVERCOOKED_API UQuickTimeEventComponent : public UActorComponent, public IQuickTimeEvent
{
	GENERATED_BODY()

#pragma region Variables

public:
	UPROPERTY(EditDefaultsOnly)
	bool PlayerMustHaveHoldable;
	UPROPERTY(EditAnywhere)
	FString PlayerHoldableName;
	UPROPERTY(EditDefaultsOnly)
	bool MustHaveHoldable;
	UPROPERTY(EditDefaultsOnly)
	FString HoldableName;

protected:
	UPROPERTY()
	APlayerCharacter* MyPlayerCharacter;

private:
	UPROPERTY(BlueprintAssignable)
	FOnInitialize OnInitialize;
	UPROPERTY(BlueprintAssignable)
	FOnInitializeWithHoldable OnInitializeWithHoldable;
	UPROPERTY(BlueprintAssignable)
	FOnActionFinished OnActionFinished;
	UPROPERTY()
	TArray<UQuickTimeEventAction*> Actions;
	UPROPERTY()
	int CurrentActionIndex = 0;
	UPROPERTY()
	bool Running;
	UPROPERTY()
	float Timer;
	UPROPERTY()
	float Progress;

	UPROPERTY()
	bool Finished;

	const float TIMER_MULTIPLIER = 0.025f;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this component's properties
	UQuickTimeEventComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//IQuickTimeEvent Interface
	virtual void Initialize(APlayerCharacter* playerCharacter) override;
	virtual bool CanInitialize(APlayerCharacter* playerCharacter) const override;
	UFUNCTION(BlueprintCallable)
	virtual bool IsRunning() const override;
	UFUNCTION(BlueprintCallable)
	virtual float GetProgress() const override;
	virtual void Finish() override;

	UFUNCTION(BlueprintCallable)
	virtual FString GetCurrentActionName() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetPlayerHoldableName(FString NewPlayerHoldableName);

	virtual UEnhancedPlayerInput* ExtractPlayerInput(const APlayerCharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddPressAction(UInputAction* InputAction, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddPressActionVector2D(UInputAction* InputAction, FVector2D Vector, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddHoldAction(UInputAction* InputAction, float HoldTime, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddHoldActionVector2D(UInputAction* InputAction, FVector2D Vector, float HoldTime, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddMashAction(UInputAction* InputAction, int MashCount, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddMashActionVector2D(UInputAction* InputAction, FVector2D Vector, int MashCount, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddWiggleAction(UInputAction* InputAction, int WiggleCount, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual UQuickTimeEventAction* AddMashPairAction(UInputAction* FirstInputAction, UInputAction* SecondInputAction, int MashCount, FString Name);

	UFUNCTION(BlueprintCallable)
	virtual void RandomizeActionsOrder();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

#pragma endregion		
};
