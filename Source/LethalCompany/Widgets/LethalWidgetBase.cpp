// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalWidgetBase.h"
#include "../LethalPlayerState.h"
#include "../Employee.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void ULethalWidgetBase::NativeConstruct()
{
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaB")));

	ALethalPlayerState* LethalPlayerState = Cast<ALethalPlayerState>(GetOwningPlayerPawn()->GetPlayerState());

	if (LethalPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail BindLethalWidget"));
	}
	else if (IsValid(LethalPlayerState))
	{
		UE_LOG(LogTemp, Warning, TEXT("BindLethalWidget"))
		LethalPlayerState->OnChangeStaminaRatio.AddDynamic(this, &ULethalWidgetBase::SetStaminaRatio);
	}
}

void ULethalWidgetBase::SetStaminaRatio(float NewStaminaRatio)
{
	StaminaBar->SetPercent(NewStaminaRatio);
}
