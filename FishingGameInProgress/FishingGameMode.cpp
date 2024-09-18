// Copyright Epic Games, Inc. All Rights Reserved.

#include "FishingGameMode.h"
#include "FishingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFishingGameMode::AFishingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Content/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
