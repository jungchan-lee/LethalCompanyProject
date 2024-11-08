// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ALobbyGameStateBase::OnRep_PlayerCount()
{
	if (OnChangePlayerCount.IsBound())
	{
		OnChangePlayerCount.Broadcast((uint32)PlayerCount);
	}
}

void ALobbyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameStateBase, PlayerCount);
}
