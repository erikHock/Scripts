// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THRIDPSHOOTER_API IIUsable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/* Method for object stored in inventory */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Use();
};
