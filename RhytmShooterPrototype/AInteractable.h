// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Interfaces/IInteractable.h"
#include "Kismet/GameplayStatics.h"
#include "AInteractable.generated.h"

class UStaticMeshComponent;
class AABaseWeapon;
class UUEventBus;
class AThridPShooterGameMode;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS()
class THRIDPSHOOTER_API AAInteractable : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAInteractable();

	/* Storable actor reference for spawn in invetory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	TSubclassOf<AABaseWeapon> BaseWeaponTemplate = nullptr;

	/* Must have base weapon template */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	bool bCanBeStoredInInventory = false;

	/* Mesh of interactable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
	
	UPROPERTY(BlueprintAssignable);
	FOnInteract OnInteract;

private:
	/* If can interact with player */
	bool bCanInteract = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Interact_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
