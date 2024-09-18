// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BW_BeatWidget.generated.h"

/**
 * 
 */
UCLASS()
class THRIDPSHOOTER_API UBW_BeatWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere)
	float InitialXPos = 150.0f;

	UPROPERTY(EditAnywhere)
	float EndXPos = 0.0f;
	
	UFUNCTION()
	void InitMove(const float& BDuration, const float& BBeginTimestamp);

private:
	UFUNCTION()
	float CalculateAlpha(const float& BDuration, const float& BBeginTimestamp);

	UPROPERTY()
	bool bCanMove = false;

	UPROPERTY()
	float BeatDuration = 0.0f;

	UPROPERTY()
	float BeatBeginTimestamp = 0.0f;
};
