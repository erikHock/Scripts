// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Interfaces/IUsable.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryComponent.generated.h"

class AAInteractable;
class AABaseWeapon;
class UUEventBus;
class AThridPShooterGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, AABaseWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponChanged, AABaseWeapon*, Weapon, AABaseWeapon*, PreviousWeapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THRIDPSHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<AABaseWeapon*> Items;

	UFUNCTION()
	void AddItem(TSubclassOf<AABaseWeapon> ActorToAdd);

	UFUNCTION()
	void RemoveItem(AABaseWeapon* ActorToRemove);
	
	UFUNCTION()
	void NextItem();

	UFUNCTION()
	void PreviousItem();

	UFUNCTION()
	void UseItem();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnWeaponAdded OnWeaponAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnWeaponChanged OnWeaponChanged;

	FORCEINLINE AABaseWeapon* GetCurrentItem() { return CurrentItem; }

private:
	UPROPERTY()
	AABaseWeapon* CurrentItem = nullptr;

	UPROPERTY()
	AABaseWeapon* PreviousCurrentItem = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
