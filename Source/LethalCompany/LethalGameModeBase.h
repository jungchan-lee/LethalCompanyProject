// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LethalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ALethalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsIngame = true;
};
