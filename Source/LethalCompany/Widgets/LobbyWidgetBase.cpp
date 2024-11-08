// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "../LobbyGameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void ULobbyWidgetBase::NativeConstruct()
{
	PlayerCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerCount")));
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidgetBase::StartButtonClicked);
	}

	ALobbyGameStateBase* LobbyGameState = Cast<ALobbyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (IsValid(LobbyGameState))
	{
		LobbyGameState->OnChangePlayerCount.AddDynamic(this, &ULobbyWidgetBase::SetPlayerCount);
	}
}

void ULobbyWidgetBase::StartButtonClicked()
{
	GetWorld()->ServerTravel(TEXT("InGame"));
}

void ULobbyWidgetBase::SetPlayerCount(uint32 NewPlayerCount)
{
	FString Temp = FString::Printf(TEXT("%d Player"), NewPlayerCount);

	PlayerCount->SetText(FText::FromString(Temp));
}
