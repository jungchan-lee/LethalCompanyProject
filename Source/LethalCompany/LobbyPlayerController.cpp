// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Widgets/LobbyWidgetBase.h"
#include "Components/Button.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FSoftClassPath LobbyWidgetClassPath(TEXT("/Game/Hyunjun/Widgets/WBP_LobbyWidget.WBP_LobbyWidget_C"));
	if (IsLocalPlayerController())
	{
		UClass* WidgetClass = LobbyWidgetClassPath.TryLoadClass<ULobbyWidgetBase>();
		if (IsValid(WidgetClass))
		{
			LobbyWidget = CreateWidget<ULobbyWidgetBase>(this, WidgetClass);
			if (IsValid(LobbyWidget))
			{
				LobbyWidget->AddToViewport();
				SetInputMode(FInputModeGameAndUI());
				SetShowMouseCursor(true);

				if (GetLocalRole() == ENetRole::ROLE_Authority && GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
				{
					LobbyWidget->ShowStartButton(true);
				}
				else
				{
					LobbyWidget->ShowStartButton(false);
				}
			}

		}
	}
}
