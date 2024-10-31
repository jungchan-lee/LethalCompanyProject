// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "TitleButtonBase.generated.h"

class UTitleButtonTextBase;
/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API UTitleButtonBase : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTitleButtonTextBase> ButtonText;
};
