// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Pawn = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(Pawn))
	{
		Velocity = Pawn->GetCharacterMovement()->Velocity;
		GroundSpeed = Pawn->GetCharacterMovement()->Velocity.Size2D();
		bShouldMove = (UKismetMathLibrary::NotEqual_VectorVector(Pawn->GetCharacterMovement()->GetCurrentAcceleration(), FVector::Zero(), 0.0f) && GroundSpeed > 3.0f);
		bIsFalling = Pawn->GetCharacterMovement()->IsFalling();

		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Pawn->GetActorRotation());
	}
}