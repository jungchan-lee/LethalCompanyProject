// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalPlayerState.h"
#include "LethalPlayerController.h"
#include "Net/UnrealNetwork.h"

void ALethalPlayerState::CalculateStamina(float DeltaTime)
{
	if (!IsRun)
	{
		if (StaminaRatio >= 100.0f)
		{
			StaminaRatio = 100.0f;
		}
		else if (StaminaRatio >= 0.0f && StaminaRatio < 100.0f)
		{
			StaminaRatio += DeltaTime * 2.0f;
			UE_LOG(LogTemp, Warning, TEXT("%f"), StaminaRatio);
		}
	}
	else if(IsRun)
	{
		if (StaminaRatio <= 0.0f)
		{
			StaminaRatio = 0.0f;
			IsRun = false;
		}
		else if (StaminaRatio > 0.0f && StaminaRatio <= 100.0f)
		{
			StaminaRatio -= DeltaTime * 8.0f;
			UE_LOG(LogTemp, Warning, TEXT("%f"), StaminaRatio);
		}
	}
}

void ALethalPlayerState::OnRep_StaminaRatio()
{
	if (OnChangeStaminaRatio.IsBound())
	{
		OnChangeStaminaRatio.Broadcast((float)StaminaRatio);
	}
}

void ALethalPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALethalPlayerState, StaminaRatio);
}
