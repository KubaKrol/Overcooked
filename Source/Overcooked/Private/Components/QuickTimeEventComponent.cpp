// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickTimeEventComponent.h"
#include "Overcooked/Public/Player/PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Overcooked/Public/Components/HolderComponent.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventPressAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventPressActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventHoldAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventHoldActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventMashAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventMashActionV2D.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventWiggleAction.h"
#include "Overcooked/Public/QuickTimeEvent/QuickTimeEventMashPairAction.h"

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

	if (CurrentActionIndex < Actions.Num() && Running)
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

	if (GetProgress() >= 1.0f)
	{
		Finish();
		return;
	}

	if (Running)
	{
		float maxProgress = (float)Actions.Num();
		float progressSum = 0.0f;
		for (int i = 0; i < Actions.Num(); i++)
		{
			progressSum += Actions[i]->GetProgress();
		}

		Timer += GetWorld()->DeltaTimeSeconds * TIMER_MULTIPLIER;
		Progress = Timer + (progressSum / maxProgress);
	}
}

void UQuickTimeEventComponent::Initialize(APlayerCharacter* playerCharacter)
{
	if (!CanInitialize(playerCharacter))
		return;

	CurrentActionIndex = 0;
	Actions.Empty();
	MyPlayerCharacter = playerCharacter;
	MyPlayerCharacter->SetQuickTimeEvent(this);
	OnInitialize.Broadcast();
	Progress = 0.0f;
	Timer = 0.0f;
	Running = true;

	if (PlayerMustHaveHoldable) 
	{
		OnInitializeWithHoldable.Broadcast(playerCharacter->GetHolderComponent()->GetHoldable()->GetHoldableName());
	}
}

bool UQuickTimeEventComponent::CanInitialize(APlayerCharacter* playerCharacter) const
{
	//if(Finished)
		//return false;

	if(Running)
		return false;

	if (MyPlayerCharacter != nullptr)
		return false;

	if (PlayerMustHaveHoldable)
	{
		if (!playerCharacter->GetHolderComponent()->IsHolding())
			return false;

		if (playerCharacter->GetHolderComponent()->GetHoldable()->GetHoldableName() != PlayerHoldableName)
			return false;
	}

	if (MustHaveHoldable)
	{
		UHolderComponent* MyHolderComponent = Cast<UHolderComponent>(GetOwner()->GetComponentByClass(UHolderComponent::StaticClass()));

		if (!MyHolderComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("QTE component must hold holdable to initialize but does not have Holder Component! Fix it!"));
			return false;
		}

		if (!MyHolderComponent->IsHolding())
			return false;

		if (MyHolderComponent->GetHoldable()->GetHoldableName() != HoldableName)
			return false;
	}

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
	if (Running)
	{
		Progress = 0.0f;
		Running = false;
		Finished = true;

		OnFinished.Broadcast();

		if (MyPlayerCharacter != nullptr)
		{
			MyPlayerCharacter->SetQuickTimeEvent(nullptr);
			MyPlayerCharacter = nullptr;
		}
	}
}

FString UQuickTimeEventComponent::GetCurrentActionName() const
{
	if (Actions.Num() == 0)
		return "";

	if (Actions[CurrentActionIndex] == nullptr)
		return "";

	return Actions[CurrentActionIndex]->GetName();
}

void UQuickTimeEventComponent::SetPlayerHoldableName(FString NewPlayerHoldableName)
{
	PlayerHoldableName = NewPlayerHoldableName;
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

UQuickTimeEventAction* UQuickTimeEventComponent::AddMashPairAction(UInputAction* FirstInputAction, UInputAction* SecondInputAction, int MashCount, FString Name)
{
	UQuickTimeEventMashPairAction* MashPairAction = NewObject<UQuickTimeEventMashPairAction>(this);
	MashPairAction->Init(ExtractPlayerInput(MyPlayerCharacter), FirstInputAction, SecondInputAction, MashCount, Name);
	Actions.Add(Cast<UQuickTimeEventAction>(MashPairAction));
	return Cast<UQuickTimeEventAction>(MashPairAction);
}

void UQuickTimeEventComponent::RandomizeActionsOrder()
{
	//TODO
}

