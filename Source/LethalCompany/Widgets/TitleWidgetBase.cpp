// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "SocketSubsystem.h"
#include "../LethalGameInstanceSubsystem.h"

void UTitleWidgetBase::NativeConstruct()
{
	StartServerButton = Cast<UButton>(GetWidgetFromName(TEXT("StartServerBtn")));
	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));
	//ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP")));
	UserName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("UserNameBox")));

	if (StartServerButton)
	{
		StartServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessStartServerButtonClick);
	}

	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessConnectButtonClick);
	}
}

void UTitleWidgetBase::ProcessStartServerButtonClick()
{
	//SaveUserName();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void UTitleWidgetBase::ProcessConnectButtonClick()
{
	SaveUserName();
	//UGameplayStatics::OpenLevel(GetWorld(), FName(*ServerIP->GetText().ToString()));
}

void UTitleWidgetBase::SaveUserName()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	ULethalGameInstanceSubsystem* LethalSubsystem = GameInstance->GetSubsystem<ULethalGameInstanceSubsystem>();
	if (IsValid(LethalSubsystem))
	{
		LethalSubsystem->UserName = UserName->GetText().ToString();
	}
}
