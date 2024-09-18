// Fill out your copyright notice in the Description page of Project Settings.


#include "BW_BeatWidget.h"

void UBW_BeatWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCanMove)
	{
		if (FMath::IsNearlyEqual(GetRenderTransform().Translation.X, EndXPos))
		{
			SetRenderTranslation(FVector2D(InitialXPos, 0.0f));
			SetVisibility(ESlateVisibility::Hidden);
			bCanMove = false;
		}
		else
		{
			float Alpha = CalculateAlpha(BeatDuration, BeatBeginTimestamp);
			SetRenderTranslation(FVector2D(FMath::Lerp(GetRenderTransform().Translation.X, EndXPos, 0.3f), 0.0f));
		}
	}
}

void UBW_BeatWidget::InitMove(const float& BDuration, const float& BBeginTimestamp)
{
	SetVisibility(ESlateVisibility::Visible);
	BeatDuration = BDuration;
	BeatBeginTimestamp = BBeginTimestamp;
	bCanMove = true;
	
}

float UBW_BeatWidget::CalculateAlpha(const float& BDuration, const float& BBeginTimestamp)
{
	float ElapsedTime = FPlatformTime::Seconds() - BBeginTimestamp;
	ElapsedTime = FMath::Clamp(ElapsedTime, 0.0f, BDuration);
	const float Alpha = ElapsedTime / BDuration;
	return Alpha;
}


