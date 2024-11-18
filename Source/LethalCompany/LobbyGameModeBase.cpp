// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "LobbyGameStateBase.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	ALobbyGameStateBase* LobbyGameState = GetGameState<ALobbyGameStateBase>();

	if (IsValid(LobbyGameState))
	{
		LobbyGameState->PlayerCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			LobbyGameState->PlayerCount++;
			LobbyGameState->OnRep_PlayerCount();
		}
	}

	Super::PostLogin(NewPlayer);
}

void ALobbyGameModeBase::Logout(AController* Exiting)
{
	ALobbyGameStateBase* LobbyGameState = GetGameState<ALobbyGameStateBase>();
	if (IsValid(LobbyGameState))
	{
		LobbyGameState->PlayerCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			LobbyGameState->PlayerCount++;
		}

		LobbyGameState->PlayerCount--;
		LobbyGameState->OnRep_PlayerCount();
	}

	Super::Logout(Exiting);
}
