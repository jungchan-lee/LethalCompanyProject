// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "Flashlight.h"
#include "Shovel.h"
#include "LethalPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AEmployee::AEmployee()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EmployeeMesh(TEXT("/Game/Assets/Employee/Meshes/SM_Employee.SM_Employee"));
	if (EmployeeMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EmployeeMesh.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	Gastank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gastank"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GastankMesh(TEXT("/Game/Assets/Employee/Meshes/Gastank.Gastank"));
	if (GastankMesh.Succeeded())
	{
		Gastank->SetStaticMesh(GastankMesh.Object);
	}

	Gastank->K2_AttachToComponent(GetMesh(), TEXT("gastank"),EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	Gastank->bOwnerNoSee = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = -180.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	IsShovel = false;

	bReplicates = true;
}

void AEmployee::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyPlayerController = Cast<APlayerController>(GetController());

	if (IsValid(MyPlayerController))
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(MyPlayerController->GetLocalPlayer());

		if (IsValid(LocalPlayer))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (InputMappingContext)
				{
					InputSystem->AddMappingContext(InputMappingContext, 0);
				}
			}
		}
	}

	Flashlight = GetWorld()->SpawnActor<AFlashlight>(AFlashlight::StaticClass(), GetActorTransform());
	Flashlight->K2_AttachToComponent(GetMesh(), TEXT("flashlight"), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	Flashlight->Mesh->SetVisibility(false);

	Shovel = GetWorld()->SpawnActor<AShovel>(AShovel::StaticClass(), GetActorTransform());
	Shovel->K2_AttachToComponent(GetMesh(), TEXT("shovel"), EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	Shovel->Mesh->SetVisibility(false);
}

void AEmployee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEmployee::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AEmployee::Move);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AEmployee::Look);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AEmployee::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AEmployee::StopJumping);
		//EIC->BindAction(IA_Flashlight, ETriggerEvent::Completed, this, &AEmployee::ToggleFlashlight);
		//IC->BindAction(IA_TurnFlashlight, ETriggerEvent::Completed, this, &AEmployee::ToggleTurnFlashlight);
		//EIC->BindAction(IA_Shovel, ETriggerEvent::Completed, this, &AEmployee::ToggleShovel);
		//EIC->BindAction(IA_ShovelAttack, ETriggerEvent::Completed, this, &AEmployee::PlayShovelAttack);
	}

}

void AEmployee::Move(const FInputActionValue& Value)
{
	if (IsDead) return;

	FVector2D Temp = Value.Get<FVector2D>();
	FVector Direction(FVector(Temp.Y, Temp.X, 0));
	Direction.Normalize();

	FRotator AbsoluteRotation = GetControlRotation();
	FRotator ForwardRotation(0, AbsoluteRotation.Yaw, 0);

	FVector ForwardVectorXYPlaneBase = UKismetMathLibrary::GetForwardVector(ForwardRotation);

	FVector RightVectorXYPlaneBase = UKismetMathLibrary::GetRightVector(ForwardRotation);

	AddMovementInput(ForwardVectorXYPlaneBase * Temp.Y);
	AddMovementInput(RightVectorXYPlaneBase * Temp.X);
}

void AEmployee::Look(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<FVector2D>().Y);
	AddControllerYawInput(Value.Get<FVector2D>().X);
}

void AEmployee::Dead()
{
	GetMesh()->SetSimulatePhysics(true);
	IsDead = true;
}

void AEmployee::ToggleFlashlight()
{
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(FlashlightAnimMontage))
	{
		StopAnimMontage(FlashlightAnimMontage);
		Flashlight->ToggleLight();
		Flashlight->Mesh->SetVisibility(false);
	}
	else
	{
		PlayAnimMontage(FlashlightAnimMontage);
		Flashlight->ToggleLight();
		Flashlight->Mesh->SetVisibility(true);
	}
}

void AEmployee::ToggleTurnFlashlight()
{
	Flashlight->ToggleLight();
}

void AEmployee::ToggleShovel()
{
	if (IsShovel)
	{
		Shovel->Mesh->SetVisibility(false);
	}
	else
	{
		Shovel->Mesh->SetVisibility(true);
	}

	IsShovel = !IsShovel;
}

void AEmployee::PlayShovelAttack()
{
	PlayAnimMontage(ShovelAttackAnimMontage);
}
