// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThridPShooterGameMode.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Player/ThridPShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Proxy/UEventBus.h"
#include "Core_HUD.h"


AThridPShooterGameMode::AThridPShooterGameMode()
{
	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL){
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set default HUD class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ACore_HUD> PlayerHUDBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_CoreHUD"));
	if (PlayerHUDBPClass.Class != NULL) {
		HUDClass = PlayerHUDBPClass.Class;
	}

	// Creating instance of event bus
	EventBus = CreateEventBusInstance();
	
}

UUEventBus* AThridPShooterGameMode::CreateEventBusInstance() {
	UUEventBus* EBPtr = NewObject<UUEventBus>();
	return EBPtr;
}