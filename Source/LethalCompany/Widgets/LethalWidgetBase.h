// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LethalWidgetBase.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ULethalWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	void SetStaminaRatio(float NewStaminaRatio);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProgressBar* StaminaBar;
};
