// Copyright Epic Games, Inc. All Rights Reserved.


#include "OvercookedGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Overcooked/Public/Player/PlayerCharacter.h"
#include "GameFramework/PlayerStart.h"

void AOvercookedGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	for (int i = 0; i < PlayerStarts.Num(); i++)
	{
		if (i == AmountOfPlayers)
			return;

		const FVector SpawnLocation = PlayerStarts[i]->GetActorLocation();
		const FRotator SpawnRotation = PlayerStarts[i]->GetActorRotation();
		AActor* PlayerActor = GetWorld()->SpawnActor(PlayerCharacterBlueprint, &SpawnLocation, &SpawnRotation);

		if (i == 0)
		{
			//First player controller is always created, so no need to create it
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PC->Possess(Cast<APlayerCharacter>(PlayerActor));
		}
		else 
		{
			//Creating the rest of player controllers
			APlayerController* PC = UGameplayStatics::CreatePlayer(GetWorld(), i);
			PC->Possess(Cast<APlayerCharacter>(PlayerActor));
		}
	}
}
