// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Logging/LogMacros.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Interfaces/IUsable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ABaseWeapon.generated.h"

class UNiagaraSystem;
class UDA_WeaponData;

UENUM(BlueprintType)
enum class EWeaponType : uint8 {
	VE_Default UMETA(DisplayName = "Default"),
	VE_Rifle UMETA(DisplayName="Rifle"),
	VE_Pistol UMETA(DisplayName="Pistol"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShootFired);

UCLASS(Blueprintable)
class THRIDPSHOOTER_API AABaseWeapon : public AActor, public IIUsable {
	GENERATED_BODY()

private:
	
	/* Reference to player  */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerActorRef = nullptr;

	void SpawnImpactEffect(FHitResult* HitReslut,FVector& StartPos);

public:
	// Sets default values for this actor's properties
	AABaseWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::VE_Default;                  //TODO Put it in data ?

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnShootFired OnShootFired;

	bool Use_Implementation() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") 
	UNiagaraSystem* ImpactEffect;                                        //TODO Put it in data ?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UDA_WeaponData* WeaponData;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();
};

