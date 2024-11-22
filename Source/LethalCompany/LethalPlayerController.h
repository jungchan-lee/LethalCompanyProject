// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LethalPlayerController.generated.h"

class ULethalWidgetBase;

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ALethalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<ULethalWidgetBase> LethalWidget;
};
