// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Core_HUD.generated.h"

class UUW_HUD;
/** Framework class for main widget functionality */ 
UCLASS(Blueprintable)
class THRIDPSHOOTER_API ACore_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();


	/** Game HUD Class */
	UPROPERTY(EditAnywhere, Category = "GameHUD")
	TSubclassOf<UUW_HUD> TemplateGameHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameHUD")
	TObjectPtr<UUW_HUD> GameHUD;
	
	UFUNCTION()
	void CreateGameHUD();

	UFUNCTION()
	void AddOnGameHUDOnScreen();

	
};
