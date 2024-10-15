// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bShouldMove : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Direction;
};
