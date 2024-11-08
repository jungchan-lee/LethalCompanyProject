// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FSoftClassPath LobbyWidgetClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UMG/WBP_Lobby.WBP_Lobby_C'"));
}
