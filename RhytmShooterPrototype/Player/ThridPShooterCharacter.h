// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Interfaces/IInteractable.h"
#include "ThridPShooterCharacter.generated.h"

class AABaseWeapon;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInventoryComponent;
class USkeletalMeshComponent;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AThridPShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** MouseLeftButton Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MouseLeftAction;

	/** MouseRightButton Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MouseRightAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MouseWheelAction;

	
private:
	/** Trace for interactable actors **/
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	/** Trace for interactable actors **/
	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	/** Cache interactable interface pointer **/
	IIInteractable* InteractionInterface = nullptr;

	bool bIsCheckedThisFrame = false;
	
	bool bCanInteract = true;

	UPROPERTY()
	TObjectPtr<AActor> InteractableActor = nullptr;

	/* Checking with overlap sphere for interactables */
	UFUNCTION()
	void CheckForInteractablesWithTrace();
	
	UPROPERTY()
	TObjectPtr<UInventoryComponent> Inventory = nullptr;

	UPROPERTY()
	bool bHasIronSight = false;

	FTimerHandle InteractionTimer;

public:
	AThridPShooterCharacter();
	
	/** Trace for interactable actors **/
	UPROPERTY(EditAnywhere, Category = "InteractablesChecking")
	float SphereOverlapRadius = 120.0f;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE bool GetbHasIronSight() { return bHasIronSight; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FORCEINLINE void SetbHasIronSight(bool HasIronSight) { bHasIronSight = HasIronSight; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE UInventoryComponent* GetInventory() { return Inventory; }
	
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	bool bIsEquipped = false;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float Cooldown = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WhenHasIronSight = 250.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WhenHasNotIronSight = 500.f;

	UPROPERTY(EditAnywhere, Category = "CameraCustom")
	float ArmLengthHasIronSight = 50.0f;

	UPROPERTY(EditAnywhere, Category = "CameraCustom")
	float ArmLengthHasNotIronSight = 350.0f;

	UPROPERTY(EditAnywhere, Category = "CameraCustom")
	FVector BoomLocHasIronSight = FVector(0.0, 42.0, 70.0);

	UPROPERTY(EditAnywhere, Category = "CameraCustom")
	FVector BoomLocHasNotIronSight = FVector(0.0, 0.0, 30);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraCustom")
	FName CharacterMeshSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraCustom")
	USkeletalMeshComponent* CharacterMeshRef;

	UFUNCTION(BlueprintCallable, Category = "CameraCustom")
	void SetCameraToBase();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for click input */
	void MouseLeftButton(const FInputActionValue& Value);

	/* Aiming iron sights */
	void MouseRightButtonClicked(const FInputActionValue& Value);
	
	/* Aiming iron sights */
	void MouseRightButtonReleased(const FInputActionValue& Value);
	
	/* Scroll weapons up */
	void MouseWheel(const FInputActionValue& Value);

	/** Called for interacting with interactable input */
	void Interact(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

