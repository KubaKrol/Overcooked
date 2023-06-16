// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

class UMainWidget;
class UClientCard;
class AClient;

/**
 * 
 */
UCLASS()
class OVERCOOKED_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()
	
#pragma region Variables

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetBlueprint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ClientCardWidgetBlueprint;
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> ClientCardsViewportPositions;

protected:

private:
	UPROPERTY(VisibleAnywhere)
	UMainWidget* MainWidget;
	UPROPERTY(VisibleAnywhere)
	TArray<UClientCard*> ClientCards;

#pragma endregion

#pragma region Methods

public:
	UFUNCTION(BlueprintCallable)
	void AddClientCard(AClient* Client);

	UFUNCTION(BlueprintCallable)
	void RemoveClientCard(AClient* Client);

	UFUNCTION(BlueprintCallable)
	UMainWidget* GetMainWidget();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	void HandleClientCardsPositions();

#pragma endregion
};
