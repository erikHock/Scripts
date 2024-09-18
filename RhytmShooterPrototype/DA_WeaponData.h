// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_WeaponData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THRIDPSHOOTER_API UDA_WeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DrawingWeaponAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DrawingWeaponBackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName DrawingWeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName DrawingWeaponBackSocket;
	
};
