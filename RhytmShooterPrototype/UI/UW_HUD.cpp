// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_HUD.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include <ThridPShooter/Proxy/UEventBus.h>
#include <ThridPShooter/Core/ThridPShooterGameMode.h>

#include "BW_BeatWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

//#define DEBUG_ON_SCREEN



void UUW_HUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

#ifdef DEBUG_ON_SCREEN
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TickInWIdget"));
#endif
}

void UUW_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Get and cache event bus from Game Mode
	AThridPShooterGameMode* GM = Cast<AThridPShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	EventBus = GM->GetEventBus();

	ensureMsgf(EventBus != nullptr, TEXT("EventBus is nullptr"));
	EventBus->OnBeatEventHUD.AddDynamic(this, &UUW_HUD::HandleWidgetsRendPosX);

	CreateBeatWidgets();
	SetupWidgetsPosToCenter();

	// Set widgets start position
	for (int32 i = 0; i < BeatWidgets.Num(); i++)
	{
		SetWidgetRendPosXY(BeatWidgets[i], 150.0f, 0.0f);
	}
	// Disable widgets
	// Widgets is prepared for pool
	for (int32 i = 0; i < BeatWidgets.Num(); i++) {
		BeatWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUW_HUD::CreateBeatWidgets()
{
	UCanvasPanel* Canvas = Cast<UCanvasPanel>(GetRootWidget());
	
	if (Canvas)
	{
		for (int32 i = 0; i < CountPerSide; i++)
		{
			UUserWidget* BW = CreateWidget<UUserWidget>(Canvas, BeatWidgetTemplate, FName("BW"));
			Canvas->AddChild(BW);
			BeatWidgets.Add(BW);
		}
	}
}

void UUW_HUD::DisableWidget(UUserWidget* Widget) {
	for (int32 i = 0; i < BeatWidgets.Num(); i++) {
		BeatWidgets[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUW_HUD::SetupWidgetsPosToCenter() {
	ensureMsgf(BeatWidgets.Num() != 0, TEXT("Beat widgets array is empty!"));
	FVector2D CenteredPos = FVector2D(0.5f, 0.5f);
	
	for (int32 i = 0; i < BeatWidgets.Num(); i++)
	{
		UCanvasPanelSlot* Slt = Cast<UCanvasPanelSlot>(BeatWidgets[i]->Slot);
		Slt->SetAnchors(FAnchors(CenteredPos.X,CenteredPos.Y));
		Slt->SetAlignment(CenteredPos);
		Slt->SetPosition(FVector2D(0.0f, 0.0f));
	}
}

void UUW_HUD::SetWidgetRendPosXY(UUserWidget* Widget,float PosX, float PosY)
{
	FWidgetTransform Transform = Widget->GetRenderTransform();
	Transform.Translation.X = PosX;
	Transform.Translation.Y = PosY;
	Widget->SetRenderTransform(Transform);
}

void UUW_HUD::HandleWidgetsRendPosX(float BeatDuration, float BeatBeginTimestamp) {
	UUserWidget* BeatWidget = nullptr;

	// Get disabled widget from the pool
	for (int32 i = 0; i < BeatWidgets.Num(); i++)
	{
		if (BeatWidgets[i]->GetVisibility() == ESlateVisibility::Hidden)
		{
			BeatWidget = BeatWidgets[i];
			break;
		}
	}
	
	UBW_BeatWidget* CurrentBeatWidget  = Cast<UBW_BeatWidget>(BeatWidget);

	// Move from right to center
	ensureMsgf(CurrentBeatWidget, TEXT("Current beat widget is null"));
	CurrentBeatWidget->InitMove(BeatDuration, BeatBeginTimestamp);
	
	
#ifdef DEBUG_ON_SCREEN	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BeatEvent"));
#endif
}
