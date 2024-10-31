// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleButtonTextBase.h"
#include "Styling/SlateColor.h"

void UTitleButtonTextBase::ChangeTextColor()
{
	if (IsBlack)
	{
		SetColorAndOpacity(FSlateColor(FLinearColor(0.895f, 0.104f, 0.0f, 1.0f)));
	}
	else if (!IsBlack)
	{
		SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)));
	}

	IsBlack = !IsBlack;
}
