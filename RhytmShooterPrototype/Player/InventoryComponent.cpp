// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/AInteractable.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/ABaseWeapon.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Proxy/UEventBus.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Core/ThridPShooterGameMode.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get EB instance from game mode
	AThridPShooterGameMode* GM = Cast<AThridPShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UUEventBus* EB = GM->GetEventBus();

	// Bind event to EB
	checkf(EB != nullptr, TEXT("EventBus pointer is null, InventoryComponent"));
	EB->OnInteractableEvent.AddDynamic(this, &UInventoryComponent::AddItem);

}

// Spawn item from reference and add it to inventory 
void UInventoryComponent::AddItem(TSubclassOf<AABaseWeapon> ActorToAdd) {
	AABaseWeapon* NewItem = GetWorld()->SpawnActor<AABaseWeapon>(ActorToAdd, GetOwner()->GetTransform());

	checkf(NewItem, TEXT("Spawned weapon is null"));
	
	// Cache previous item
	/*if (CurrentItem != nullptr) {
		PreviousCurrentItem = CurrentItem;
	}*/
	
	CurrentItem = NewItem;

	Items.Add(NewItem);
	
	// Fire event for blueprint where attaching is handled
	OnWeaponAdded.Broadcast(NewItem);

	//OnWeaponChanged.Broadcast(CurrentItem, PreviousCurrentItem);

}

void UInventoryComponent::RemoveItem(AABaseWeapon* ActorToRemove) {
	Items.Remove(ActorToRemove);
	
}

void UInventoryComponent::NextItem() {
	if (Items.Num() == 0 || Items.Num() == 1) {
		return;
	}
	
	int32 Index = 0;
	UE_LOG(LogTemp, Warning, TEXT("ItemsNum: %d"), Items.Num());

	// Find current item index
	int32 CurrentIndex = Items.IndexOfByKey(CurrentItem);

	// We need next index
	Index = CurrentIndex + 1;
	UE_LOG(LogTemp, Warning, TEXT("FinalIndex: %d"), Index);

	// Ensure for out of array
	if (Index > Items.Num() - 1) { Index = 0; }
	UE_LOG(LogTemp, Warning, TEXT("CurrentInventoryIndexIs: %d"), Index);

	checkf(Items.IsValidIndex(Index), TEXT("Items[Index] is not valid"));
	
	// Cache previous item
	if (CurrentItem != nullptr) {
		PreviousCurrentItem = CurrentItem;
	}
	
	CurrentItem = Items[Index];
	
	OnWeaponChanged.Broadcast(Items[Index], PreviousCurrentItem);
	
}

void UInventoryComponent::PreviousItem() {
	if (Items.Num() == 0 || Items.Num() == 1) {
		return;
	}

	// Find Item index 
	int32 Index = 0;
	
	// Find current item index
	int32 CurrentIndex = Items.IndexOfByKey(CurrentItem);
	
	// We need next index
	Index = CurrentIndex - 1;

	// Ensure for out of array
	if (Index < 0) { Index = Items.Num() - 1; }
	checkf(Items.IsValidIndex(Index), TEXT("Items[Index] is not valid"));

	// Cache previous item
	if (CurrentItem != nullptr) {
		PreviousCurrentItem = CurrentItem;
	}

	CurrentItem = Items[Index];
	
	OnWeaponChanged.Broadcast(Items[Index], PreviousCurrentItem);
	UE_LOG(LogTemp, Warning, TEXT("CurrentInventoryIndexIs: %d"), Index);
}

void UInventoryComponent::UseItem() {
	if (Items.IsEmpty()) {
		return;
	}

	IIUsable* UsableInterface = Cast<IIUsable>(CurrentItem);
	if (UsableInterface) {
		UsableInterface->Use_Implementation();
	}
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

