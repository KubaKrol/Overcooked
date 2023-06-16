// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainWidget.h"

void UMainWidget::SetClientCardsSlots(TArray<UNamedSlot*> Slots)
{
	ClientCardsSlots = Slots;
}

TArray<UNamedSlot*> UMainWidget::GetClientCardsSlots()
{
	return ClientCardsSlots;
}
