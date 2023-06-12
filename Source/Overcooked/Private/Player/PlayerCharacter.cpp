// Fill out your copyright notice in the Description page of Project Settings.

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "Overcooked/Public/Input/InputConfigData.h"
#include "Overcooked/Public/Player/PlayerSettings.h"
#include "Overcooked/Public/Actors/HolderActor.h"
#include "Overcooked/Public/Actors/Item.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/Interfaces/Interactable.h"
#include "Overcooked/Public/Interfaces/Holder.h"
#include "Overcooked/Public/Interfaces/QuickTimeEvent.h"
#include "Overcooked/Public/Components/HolderComponent.h"
#include "Overcooked/Public/Components/InteractableComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_Visibility);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    HolderComponent = CreateDefaultSubobject<UHolderComponent>(TEXT("Holder"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    // Get the EnhancedInputComponent
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    // Bind the actions
    EnhancedInputComponent->BindAction(InputActions->InputMovement, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
    EnhancedInputComponent->BindAction(InputActions->InputPrimaryAction, ETriggerEvent::Started, this, &APlayerCharacter::PrimaryAction);
    EnhancedInputComponent->BindAction(InputActions->InputSecondaryAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SecondaryAction);
    EnhancedInputComponent->BindAction(InputActions->InputThrow, ETriggerEvent::Started, this, &APlayerCharacter::Throw);
    EnhancedInputComponent->BindAction(InputActions->InputDash, ETriggerEvent::Started, this, &APlayerCharacter::Dash);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        if (MoveValue.Length() > 0.0f)
        {
            AddMovementInput(FVector(MoveValue.Y, MoveValue.X, 0.0f), MoveValue.Length());
            FQuat TargetRotation = FQuat::Slerp(
                RootComponent->GetRelativeRotation().Quaternion(),
                FVector(MoveValue.Y, MoveValue.X, 0.0f).Rotation().Quaternion(),
                PlayerSettings->RotationSpeed * GetWorld()->GetDeltaSeconds());
            RootComponent->SetWorldRotation(TargetRotation, false);
        }
    }
}

void APlayerCharacter::PrimaryAction()
{
    TArray<AActor*> OverlappingActors;
    BoxComponent->GetOverlappingActors(OverlappingActors);

    for (AActor* OverlappingActor : OverlappingActors)
    {
        if (OverlappingActor == this)
            continue;

        TArray<UActorComponent*> Holders = OverlappingActor->GetComponentsByInterface(UHolder::StaticClass());

        for (int i = 0; i < Holders.Num(); i++)
        {
            IHolder* Holder = Cast<IHolder>(Holders[i]);
            if (Holder)
            {
                if (HolderComponent->IsHolding())
                {
                    if (!Holder->IsHolding())
                    {
                        Holder->ReceiveHoldable(HolderComponent->RemoveHoldable());
                        return;
                    }
                }

                if (Holder->IsHolding())
                {
                    if (!HolderComponent->IsHolding())
                    {
                        HolderComponent->ReceiveHoldable(Holder->RemoveHoldable());
                        return;
                    }
                }

                return;
            }
        }
    }
}

void APlayerCharacter::SecondaryAction()
{
    TArray<AActor*> OverlappingActors;
    BoxComponent->GetOverlappingActors(OverlappingActors);

    for (AActor* OverlappingActor : OverlappingActors)
    {
        if (OverlappingActor == this)
            continue;

        TArray<UActorComponent*> Interactables = OverlappingActor->GetComponentsByInterface(UInteractable::StaticClass());
        TArray<UActorComponent*> QuickTimeEvents = OverlappingActor->GetComponentsByInterface(UQuickTimeEvent::StaticClass());

        for (int i = 0; i < QuickTimeEvents.Num(); i++)
        {
            IQuickTimeEvent* QuickTimeEvent = Cast<IQuickTimeEvent>(QuickTimeEvents[i]);
            if (QuickTimeEvent)
            {
                QuickTimeEvent->Initialize(this);
                return;
            }
        }

        for (int i = 0; i < Interactables.Num(); i++)
        {
            IInteractable* Interactable = Cast<IInteractable>(Interactables[i]);
            if (Interactable)
            {
                Interactable->Interact();
                return;
            }
        }
    }
}

void APlayerCharacter::Dash()
{
    Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()))->AddImpulse(GetActorForwardVector() * 400000.0f);
}

void APlayerCharacter::Throw()
{
    if (!HolderComponent->IsHolding())
        return;

    HolderComponent->RemoveHoldable()->Throw(GetActorForwardVector() + FVector(0.0f, 0.0f, 0.5f), 300.0f);
}

