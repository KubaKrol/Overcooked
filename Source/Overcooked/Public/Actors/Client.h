// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Overcooked/Public/Global/Enums.h"
#include "Client.generated.h"

class UHoldableComponent;
class UClientData;

UCLASS()
class OVERCOOKED_API AClient : public APawn
{
	GENERATED_BODY()

#pragma region Variables

public:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Client Data")
	UClientData* ClientData;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHoldableComponent* HoldableComponent;

	UPROPERTY(VisibleAnywhere)
	int CurrentTaskIndex = 0;

#pragma endregion

#pragma region Methods

public:
	// Sets default values for this pawn's properties
	AClient();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UClientData* GetClientData() const;
	virtual EClientTask GetCurrentClientTask() const;
	virtual void IncrementClientTaskIndex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

#pragma endregion
};
