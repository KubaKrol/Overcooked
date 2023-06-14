// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickTimeEventComponent.h"
#include "Overcooked/Public/Player/PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventPressAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventPressActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventHoldAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventHoldActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventMashAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventMashActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventWiggleAction.h"

// Sets default values for this component's properties
UQuickTimeEventComponent::UQuickTimeEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuickTimeEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuickTimeEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (CurrentActionIndex < Actions.Num())
	{
		if (MyPlayerCharacter != nullptr && Actions.Num() > 0)
		{
			if (Actions[CurrentActionIndex]->CheckInput())
			{
				OnActionFinished.Broadcast(CurrentActionIndex);
				CurrentActionIndex++;

				if (CurrentActionIndex >= Actions.Num())
				{
					Finish();
				}
			}
		}
	}

	if (Running)
	{
		float maxProgress = (float)Actions.Num();
		float progressSum = 0.0f;
		for (int i = 0; i < Actions.Num(); i++)
		{
			progressSum += Actions[i]->GetProgress();
		}
		Progress = progressSum / maxProgress;
	}
}

void UQuickTimeEventComponent::Initialize(APlayerCharacter* playerCharacter)
{
	if (!CanInitialize())
		return;

	CurrentActionIndex = 0;
	Actions.Empty();
	MyPlayerCharacter = playerCharacter;
	MyPlayerCharacter->SetQuickTimeEvent(this);
	OnInitialize.Broadcast();
	Running = true;
}

bool UQuickTimeEventComponent::CanInitialize()
{
	if(Finished)
		return false;

	if(Running)
		return false;

	if (MyPlayerCharacter != nullptr)
		return false;

	return true;
}

bool UQuickTimeEventComponent::IsRunning() const
{
	return Running;
}

float UQuickTimeEventComponent::GetProgress() const
{
	return Progress;
}

void UQuickTimeEventComponent::Finish()
{
	Running = false;
	Finished = true;

	if (MyPlayerCharacter != nullptr) 
	{
		MyPlayerCharacter->SetQuickTimeEvent(nullptr);
		MyPlayerCharacter = nullptr;
	}
}

FString UQuickTimeEventComponent::GetCurrentActionName() const
{
	if (Actions[CurrentActionIndex] == nullptr)
		return "";

	return Actions[CurrentActionIndex]->GetName();
}

UEnhancedPlayerInput* UQuickTimeEventComponent::ExtractPlayerInput(const APlayerCharacter* PlayerCharacter)
{
	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	return Subsystem->GetPlayerInput();
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddPressAction(UInputAction* InputAction, FString Name)
{
	UQuickTimeEventPressAction* PressAction = NewObject<UQuickTimeEventPressAction>(this);
	PressAction->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(PressAction));
	return Cast<UQuickTimeEventAction>(PressAction);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddPressActionVector2D(UInputAction* InputAction, FVector2D Vector, FString Name)
{
	UQuickTimeEventPressActionV2D* PressActionVector2D = NewObject<UQuickTimeEventPressActionV2D>(this);
	PressActionVector2D->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, Vector, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(PressActionVector2D));
	return Cast<UQuickTimeEventAction>(PressActionVector2D);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddHoldAction(UInputAction* InputAction, float HoldTime, FString Name)
{
	UQuickTimeEventHoldAction* HoldAction = NewObject<UQuickTimeEventHoldAction>(this);
	HoldAction->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, HoldTime, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(HoldAction));
	return Cast<UQuickTimeEventAction>(HoldAction);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddHoldActionVector2D(UInputAction* InputAction, FVector2D Vector, float HoldTime, FString Name)
{
	UQuickTimeEventHoldActionV2D* HoldActionVector2D = NewObject<UQuickTimeEventHoldActionV2D>(this);
	HoldActionVector2D->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, Vector, HoldTime, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(HoldActionVector2D));
	return Cast<UQuickTimeEventAction>(HoldActionVector2D);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddMashAction(UInputAction* InputAction, int MashCount, FString Name)
{
	UQuickTimeEventMashAction* MashAction = NewObject<UQuickTimeEventMashAction>(this);
	MashAction->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, MashCount, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(MashAction));
	return Cast<UQuickTimeEventAction>(MashAction);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddMashActionVector2D(UInputAction* InputAction, FVector2D Vector, int MashCount, FString Name)
{
	UQuickTimeEventMashActionV2D* MashAction = NewObject<UQuickTimeEventMashActionV2D>(this);
	MashAction->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, Vector, MashCount, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(MashAction));
	return Cast<UQuickTimeEventAction>(MashAction);
}

UQuickTimeEventAction* UQuickTimeEventComponent::AddWiggleAction(UInputAction* InputAction, int WiggleCount, FString Name)
{
	UQuickTimeEventWiggleAction* WiggleAction = NewObject<UQuickTimeEventWiggleAction>(this);
	WiggleAction->Init(ExtractPlayerInput(MyPlayerCharacter), InputAction, WiggleCount, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(WiggleAction));
	return Cast<UQuickTimeEventAction>(WiggleAction);
}

void UQuickTimeEventComponent::RandomizeActionsOrder()
{
	//TODO
}

