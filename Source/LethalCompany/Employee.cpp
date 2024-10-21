// Fill out your copyright notice in the Description page of Project Settings.


#include "Employee.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AEmployee::AEmployee()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EmployeeMesh(TEXT("/Game/Assets/Employee/Meshes/SM_Employee.SM_Employee"));
	if (EmployeeMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EmployeeMesh.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	Gastank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gastank"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GastankMesh(TEXT("/Game/Assets/Employee/Meshes/Gastank.Gastank"));
	if (GastankMesh.Succeeded())
	{
		Gastank->SetStaticMesh(GastankMesh.Object);
	}

	Gastank->K2_AttachToComponent(GetMesh(), TEXT("gastank"),EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = -180.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
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
}

// Called every frame
void AEmployee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
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
	}

}

void AEmployee::Move(const FInputActionValue& Value)
{
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