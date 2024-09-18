// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThridPShooterGameMode.generated.h"

class UUEventBus;
class ACoreHUD;

UCLASS(minimalapi)
class AThridPShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UUEventBus> EventBus = nullptr;

	UFUNCTION()
	UUEventBus* CreateEventBusInstance();

public:
	AThridPShooterGameMode();

	/* Getter for EventBus instance */
	UFUNCTION()
	FORCEINLINE UUEventBus* GetEventBus() { return EventBus; };
};



