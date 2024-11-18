// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "../LobbyGameStateBase.h"
#include "../LobbyGameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void ULobbyWidgetBase::NativeConstruct()
{
	PlayerCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerCt")));
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartBtn")));

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
	//GetWorld()->ServerTravel(TEXT("GameLevel_Hyunjun"));
	GetWorld()->ServerTravel(TEXT("SH_ThirdPersonMap"));
}

void ULobbyWidgetBase::SetPlayerCount(uint32 NewPlayerCount)
{
	FString Temp = FString::Printf(TEXT("%d Player"), NewPlayerCount);

	PlayerCount->SetText(FText::FromString(Temp));
}
