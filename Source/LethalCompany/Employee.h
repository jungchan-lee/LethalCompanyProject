// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Employee.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class AFlashlight;

UCLASS()
class LETHALCOMPANY_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	AEmployee();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void ToggleFlashlight();

	UFUNCTION()
	void ToggleTurnFlashlight();


public:
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Flashlight;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_TurnFlashlight;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Gastank;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AFlashlight> Flashlight;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TObjectPtr<UAnimMontage> FlashlightAnimMontage;
};
