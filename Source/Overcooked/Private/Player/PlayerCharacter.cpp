// Fill out your copyright notice in the Description page of Project Settings.

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Overcooked/Public/Input/InputConfigData.h"
#include "Overcooked/Public/Player/PlayerSettings.h"
#include "Overcooked/Public/Actors/HolderActor.h"
#include "Overcooked/Public/Actors/Item.h"
#include "Overcooked/Public/Interfaces/Holdable.h"
#include "Overcooked/Public/Interfaces/Interactable.h"
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

    HoldLocation = CreateDefaultSubobject<USceneComponent>(TEXT("HoldLocation"));
    HoldLocation->SetupAttachment(RootComponent);
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

void APlayerCharacter::ReceiveHoldable(IHoldable* Holdable)
{
    if (IsHolding())
        return;

    MyHoldable.SetInterface(Holdable);
    MyHoldable.SetObject(Holdable->_getUObject());
    MyHoldable->SetHolder(this);
}

bool APlayerCharacter::IsHolding() const
{
    if (MyHoldable != nullptr)
        return true;

    return false;
}

IHoldable* APlayerCharacter::GetHoldable() const
{
    return MyHoldable.GetInterface();
}

IHoldable* APlayerCharacter::RemoveHoldable()
{
    IHoldable* holdable = MyHoldable.GetInterface();
    MyHoldable.SetInterface(nullptr);
    MyHoldable.SetObject(nullptr);
    return holdable;
}

USceneComponent* APlayerCharacter::GetHoldingSceneComponent()
{
    return HoldLocation;
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
        IHolder* Holder = Cast<IHolder>(OverlappingActor);
        if (Holder)
        {
            if (Holder->_getUObject() == _getUObject())
                continue;

            if (IsHolding())
            {
                if (!Holder->IsHolding())
                {
                    Holder->ReceiveHoldable(RemoveHoldable());
                    return;
                }
            }

            if (Holder->IsHolding())
            {
                if (!IsHolding())
                {
                    ReceiveHoldable(Holder->RemoveHoldable());
                    return;
                }
            }

            return;
        }
    }
}

void APlayerCharacter::SecondaryAction()
{
    TArray<AActor*> OverlappingActors;
    BoxComponent->GetOverlappingActors(OverlappingActors);

    for (AActor* OverlappingActor : OverlappingActors)
    {
        IInteractable* Interactable = Cast<IInteractable>(OverlappingActor);
        if (Interactable)
        {
            Interactable->Interact();
            return;
        }
    }
}

void APlayerCharacter::Dash()
{
    Cast<UCharacterMovementComponent>(GetComponentByClass(UCharacterMovementComponent::StaticClass()))->AddImpulse(GetActorForwardVector() * 400000.0f);
}

void APlayerCharacter::Throw()
{
    if (!IsHolding())
        return;

    RemoveHoldable()->Throw(GetActorForwardVector() + FVector(0.0f, 0.0f, 0.5f), 300.0f);
}
