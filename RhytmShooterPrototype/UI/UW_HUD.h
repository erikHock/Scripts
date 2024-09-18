// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_HUD.generated.h"

class UImage;
class UUEventBus;
class AThridPShooterGameMode;
class UCanvasPanel;
class UCanvasPanelSlot;
class UBW_BeatWidget;


UCLASS()
class THRIDPSHOOTER_API UUW_HUD : public UUserWidget { //TODO RENAME TO BEAT WIDGET
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly)
	TArray<UUserWidget*> BeatWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BeatWidgetTemplate = nullptr;

	
	
	
private:
	UFUNCTION()
	void CreateBeatWidgets();
	
	UFUNCTION()
	void DisableWidget(UUserWidget* Widget);

	UFUNCTION()
	void SetupWidgetsPosToCenter();

	UFUNCTION()
	void SetWidgetRendPosXY(UUserWidget* Widget,float PosX, float PosY);

	UFUNCTION()
	void HandleWidgetsRendPosX(float BeatDuration, float BeatBeginTimestamp);

	UPROPERTY()
	UUEventBus* EventBus = nullptr;

	UPROPERTY()
	int CountPerSide = 7;
};
