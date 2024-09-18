// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteractable.h"
#include "Player/InventoryComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ABaseWeapon.h"
#include "Proxy/UEventBus.h"
#include "Core/ThridPShooterGameMode.h"

// Sets default values
AAInteractable::AAInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}


// Called when the game starts or when spawned
void AAInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AAInteractable::Interact_Implementation() {
	if (!bCanInteract) {
		return false;
	}

	if (bCanBeStoredInInventory) {
		// If item is storable 
		if (BaseWeaponTemplate != nullptr) {
			// Broadcast storable reference to from event bus
			AThridPShooterGameMode* GM = Cast<AThridPShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			UUEventBus* EB = GM->GetEventBus();
			
			checkf(EB != nullptr, TEXT("EventBus pointer is null, AInteractable"))
			EB->OnInteractableEvent.Broadcast(BaseWeaponTemplate);
		}
	}
	else {
		OnInteract.Broadcast();
	}

	// Disable Interactable Visual 
	bCanInteract = false;

	// Kill actor when is interacted
	Destroy();

	return true;
}

// Called every frame
void AAInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

