// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class LETHALCOMPANY_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void SetPlayerCount(uint32 NewPlayerCount);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UTextBlock* PlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UButton* StartButton;
};
