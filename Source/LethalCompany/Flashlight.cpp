// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AFlashlight::AFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FlashlightMesh(TEXT("/Game/Assets/Flashlight/Flashlight.Flashlight"));
	if (FlashlightMesh.Succeeded())
	{
		Mesh->SetStaticMesh(FlashlightMesh.Object);
	}

	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	Spotlight->SetupAttachment(Mesh);
	Spotlight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	Spotlight->SetRelativeLocation(FVector(0.0f, 10.5f, 4.0f));
	Spotlight->AttenuationRadius = 1000.0f;
	Spotlight->OuterConeAngle = 22.0f;
	Spotlight->SetVisibility(false);
}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlashlight::ToggleLight()
{
	if (Spotlight->IsVisible())
	{
		Spotlight->SetVisibility(false);
	}
	else
	{
		Spotlight->SetVisibility(true);
	}
}

