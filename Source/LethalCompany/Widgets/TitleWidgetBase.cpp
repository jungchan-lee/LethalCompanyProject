// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SocketSubsystem.h"
#include "../LethalGameInstanceSubsystem.h"

void UTitleWidgetBase::NativeConstruct()
{
	StartServerButton = Cast<UButton>(GetWidgetFromName(TEXT("StartServerBtn")));
	StartClientButton = Cast<UButton>(GetWidgetFromName(TEXT("StartClientBtn")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitBtn")));
	ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIPBox")));
	UserName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("UserNameBox")));
	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("ConfirmBtn")));
	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelBtn")));

	if (StartServerButton)
	{
		StartServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ShowStartServerUI);
	}

	if (StartClientButton)
	{
		StartClientButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ShowStartClientUI);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::QuitGame);
	}

	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessStartButton);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ShowStartMenuUI);
	}
}

void UTitleWidgetBase::ProcessStartButton()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	ULethalGameInstanceSubsystem* LethalSubsystem = GameInstance->GetSubsystem<ULethalGameInstanceSubsystem>();
	if (IsValid(LethalSubsystem))
	{
		LethalSubsystem->UserName = UserName->GetText().ToString();
	}

	if (IsServer)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("LobbyLevel"), true, TEXT("listen"));
	}
	else if (!IsServer)
	{

		UGameplayStatics::OpenLevel(GetWorld(), FName(*ServerIP->GetText().ToString()));
	}
}

void UTitleWidgetBase::ShowStartMenuUI()
{
	StartServerButton->SetVisibility(ESlateVisibility::Visible);
	StartClientButton->SetVisibility(ESlateVisibility::Visible);
	QuitButton->SetVisibility(ESlateVisibility::Visible);
	ServerIP->SetVisibility(ESlateVisibility::Collapsed);
	UserName->SetVisibility(ESlateVisibility::Collapsed);
	ConfirmButton->SetVisibility(ESlateVisibility::Collapsed);
	CancelButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UTitleWidgetBase::ShowStartServerUI()
{
	IsServer = true;
	StartServerButton->SetVisibility(ESlateVisibility::Collapsed);
	StartClientButton->SetVisibility(ESlateVisibility::Collapsed);
	QuitButton->SetVisibility(ESlateVisibility::Collapsed);
	UserName->SetVisibility(ESlateVisibility::Visible);
	ConfirmButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Visible);
}

void UTitleWidgetBase::ShowStartClientUI()
{
	IsServer = false;
	StartServerButton->SetVisibility(ESlateVisibility::Collapsed);
	StartClientButton->SetVisibility(ESlateVisibility::Collapsed);
	QuitButton->SetVisibility(ESlateVisibility::Collapsed);
	ServerIP->SetVisibility(ESlateVisibility::Visible);
	UserName->SetVisibility(ESlateVisibility::Visible);
	ConfirmButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Visible);
}

void UTitleWidgetBase::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Type::Quit, false);
}