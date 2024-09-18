// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UEventBus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableEvent, TSubclassOf<AABaseWeapon>, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeatEventHUD, float, BeatDuration, float, BeatBeginTimestamp);

UCLASS()
class THRIDPSHOOTER_API UUEventBus : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FInteractableEvent OnInteractableEvent;

	UPROPERTY()
	FOnBeatEventHUD OnBeatEventHUD;

};
