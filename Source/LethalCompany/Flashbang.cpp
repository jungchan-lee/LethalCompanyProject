// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashbang.h"

// Sets default values
AFlashbang::AFlashbang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FlashbangMesh(TEXT("/Game/Assets/Flashbang/SM_flashbang.SM_flashbang"));
	if (FlashbangMesh.Succeeded())
	{
		Mesh->SetStaticMesh(FlashbangMesh.Object);
	}
}

// Called when the game starts or when spawned
void AFlashbang::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashbang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

