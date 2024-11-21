// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LethalPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ALethalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHold = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsShovel = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRun = false;
};
