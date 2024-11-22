// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LethalPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangeStaminaRatio, ALethalPlayerState, OnChangeStaminaRatio, float, NewStaminaRatio);

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ALethalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CalculateStamina(float DeltaTime);

	UFUNCTION()
	void OnRep_StaminaRatio();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing = "OnRep_StaminaRatio")
	float StaminaRatio = 100.0f;

	UPROPERTY(BlueprintAssignable, Category = "Data")
	FChangeStaminaRatio OnChangeStaminaRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHold = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsShovel = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRun = false;
};
