// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangePlayerCount, ALobbyGameStateBase, OnChangePlayerCount, uint32, NewPlayerCount);

/**
 * 
 */
UCLASS()
class LETHALCOMPANY_API ALobbyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnRep_PlayerCount();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing = "OnRep_PlayerCount")
	uint8 PlayerCount = 0;

	UPROPERTY(BlueprintAssignable, Category = "Data")
	FChangePlayerCount OnChangePlayerCount;
};
