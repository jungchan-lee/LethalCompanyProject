// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "TitleButtonTextBase.generated.h"

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API UTitleButtonTextBase : public UTextBlock
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeTextColor();

public:
	bool IsBlack = false;
};
