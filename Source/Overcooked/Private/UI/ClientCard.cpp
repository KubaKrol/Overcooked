// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ClientCard.h"

void UClientCard::Init(AClient* Client)
{
	MyClient = Client;
	OnInitialize();
}

AClient* UClientCard::GetClient() const
{
	return MyClient;
}
