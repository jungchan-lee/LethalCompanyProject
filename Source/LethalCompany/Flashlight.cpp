// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"

// Sets default values
AFlashlight::AFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

