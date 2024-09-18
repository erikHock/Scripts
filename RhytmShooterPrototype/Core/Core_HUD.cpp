// Fill out your copyright notice in the Description page of Project Settings.


#include "Core_HUD.h"
#include <ThridPShooter/UI/UW_HUD.h>


void ACore_HUD::BeginPlay() {
	CreateGameHUD();
	AddOnGameHUDOnScreen();
}

void ACore_HUD::CreateGameHUD() {
	GameHUD = CreateWidget<UUW_HUD>(GetOwningPlayerController(), TemplateGameHUD, FName("HUD"));
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	Mode.SetHideCursorDuringCapture(false);
}

void ACore_HUD::AddOnGameHUDOnScreen() {
	GameHUD->AddToViewport(9999);
}

