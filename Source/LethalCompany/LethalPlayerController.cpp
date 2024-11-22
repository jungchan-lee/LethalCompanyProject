// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalPlayerController.h"
#include "Widgets/LethalWidgetBase.h"

void ALethalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FSoftClassPath LethalWidgetClassPath(TEXT("/Game/Hyunjun/Widgets/WBP_LethalWidget.WBP_LethalWidget_C"));

	if (IsLocalPlayerController())
	{
		UClass* WidgetClass = LethalWidgetClassPath.TryLoadClass<ULethalWidgetBase>();
		if (IsValid(WidgetClass))
		{
			LethalWidget = CreateWidget<ULethalWidgetBase>(this, WidgetClass);
			if (IsValid(LethalWidget))
			{
				LethalWidget->AddToViewport();
				SetInputMode(FInputModeGameOnly());
				SetShowMouseCursor(false);
			}

		}
	}
}
