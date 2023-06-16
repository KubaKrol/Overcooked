// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Overcooked/Public/Actors/Client.h"
#include "Overcooked/Public/UI/MainWidget.h"
#include "Overcooked/Public/UI/ClientCard.h"
#include "Components/NamedSlot.h"
#include "UI/DefaultHUD.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidget == nullptr)
		MainWidget = Cast<UMainWidget>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainWidgetBlueprint, FName("MainWidget")));
}

void ADefaultHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleClientCardsPositions();
}

void ADefaultHUD::HandleClientCardsPositions()
{
	for (int i = 0; i < ClientCards.Num(); i++)
	{
		ClientCards[i]->SetPositionInViewport(ClientCardsViewportPositions[i]);
	}
}

void ADefaultHUD::AddClientCard(AClient* Client)
{
	UUserWidget* ClientCardUserWidget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), ClientCardWidgetBlueprint);
	UClientCard* ClientCard = Cast<UClientCard>(ClientCardUserWidget);
	ClientCard->Init(Client);
	ClientCard->SetRenderScale(FVector2D(0.7f, 0.7f));
	ClientCard->SetPositionInViewport(ClientCardsViewportPositions[ClientCards.Num()]);
	ClientCard->AddToViewport();
	ClientCards.Add(ClientCard);
}

void ADefaultHUD::RemoveClientCard(AClient* Client)
{
	int cardIndex = -1;

	for (int i = 0; i < ClientCards.Num(); i++)
	{
		if (ClientCards[i]->GetClient() == Client)
		{
			cardIndex = i;
			break;
		}
	}

	if (cardIndex == -1)
		return;

	ClientCards[cardIndex]->RemoveFromViewport();
	UClientCard* ClientCard = ClientCards[cardIndex];
	ClientCards.Remove(ClientCard);
}

UMainWidget* ADefaultHUD::GetMainWidget()
{
	if (MainWidget == nullptr)
		MainWidget = Cast<UMainWidget>(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainWidgetBlueprint, FName("MainWidget")));

	return MainWidget;
}
