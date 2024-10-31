// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetBase.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ProcessStartServerButtonClick();

	UFUNCTION()
	void ProcessConnectButtonClick();

	void SaveUserName();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UButton> StartServerButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UButton> ConnectButton;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	//TObjectPtr<UEditableTextBox> ServerIP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UEditableTextBox> UserName;
};