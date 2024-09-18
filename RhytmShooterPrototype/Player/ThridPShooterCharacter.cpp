// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThridPShooterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/ABaseWeapon.h"
#include "C:/Users/Erik/Documents/Unreal Projects/ThridPShooter/Source/ThridPShooter/Player/InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AThridPShooterCharacter


AThridPShooterCharacter::AThridPShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Create inventory component instance
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	// Trace for interactable actors
	ActorsToIgnore.Add(this);
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
}

void AThridPShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AThridPShooterCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Check for interactables only once per frame
	if (!bIsCheckedThisFrame) {
		// Checking for interactables
		CheckForInteractablesWithTrace();

		bIsCheckedThisFrame = true;
	}
	else {
		bIsCheckedThisFrame = false;
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Input


void AThridPShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThridPShooterCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThridPShooterCharacter::Look);

		// Shooting
		EnhancedInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Triggered, this, &AThridPShooterCharacter::MouseLeftButton);

		// Iron sight
		EnhancedInputComponent->BindAction(MouseRightAction, ETriggerEvent::Started, this, &AThridPShooterCharacter::MouseRightButtonClicked);
		EnhancedInputComponent->BindAction(MouseRightAction, ETriggerEvent::Completed, this, &AThridPShooterCharacter::MouseRightButtonReleased);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AThridPShooterCharacter::Interact);

		// MouseWheelUp
		EnhancedInputComponent->BindAction(MouseWheelAction, ETriggerEvent::Triggered, this, &AThridPShooterCharacter::MouseWheel);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AThridPShooterCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AThridPShooterCharacter::SetCameraToBase() {
	// Set iron sights
	bHasIronSight = false;
	GetCharacterMovement()->MaxWalkSpeed = WhenHasNotIronSight;

	// Move to character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Set Camera Boom location
	CameraBoom->TargetArmLength = ArmLengthHasNotIronSight;
	CameraBoom->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->SetRelativeLocation(BoomLocHasNotIronSight);
}

void AThridPShooterCharacter::Look(const FInputActionValue& Value) {
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {

		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AThridPShooterCharacter::MouseLeftButton(const FInputActionValue& Value) {
	if (bIsEquipped) {
		Inventory->UseItem();
	}
}

void AThridPShooterCharacter::MouseRightButtonClicked(const FInputActionValue& Value) {
	if (!bIsEquipped) {
		return;
	}

	// Set iron sights
	bHasIronSight = true;
	GetCharacterMovement()->MaxWalkSpeed = WhenHasIronSight;

	// Move with strafe
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Set Camera Boom location
	CameraBoom->TargetArmLength = ArmLengthHasIronSight;
	CameraBoom->AttachToComponent(CharacterMeshRef, FAttachmentTransformRules::SnapToTargetIncludingScale, CharacterMeshSocket);
	//CameraBoom->SetRelativeLocation(BoomLocHasIronSight);
}

void AThridPShooterCharacter::MouseRightButtonReleased(const FInputActionValue& Value) {
	if (!bIsEquipped) {
		return;
	}
	
	SetCameraToBase();
}

// Interact with interactables 
void AThridPShooterCharacter::Interact(const FInputActionValue& Value) {
	InteractionInterface = Cast<IIInteractable>(InteractableActor);

	if (InteractionInterface && bCanInteract) {
		bCanInteract = false;
		InteractionInterface->Interact_Implementation();
		InteractionInterface = nullptr;

		// Cooldown for interactions
		GetWorld()->GetTimerManager().SetTimer(InteractionTimer, FTimerDelegate::CreateLambda([&] { this->bCanInteract = true; }), Cooldown, false);
	}
}

void AThridPShooterCharacter::MouseWheel(const FInputActionValue& Value) {
	float CurrentValue = Value.Get<float>();

	if (CurrentValue > 0) {
		Inventory->NextItem();
	}
	else {
		Inventory->PreviousItem();
	}
}


void AThridPShooterCharacter::CheckForInteractablesWithTrace() {
	InteractableActor = nullptr;

	// Sphere overlap for finding interactables
	FVector Position = GetActorLocation();
	TArray<AActor*> OutActors;

	const bool Hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Position, SphereOverlapRadius, TraceObjectTypes, NULL, ActorsToIgnore, OutActors);
	DrawDebugSphere(GetWorld(), Position, SphereOverlapRadius, 12, FColor::Red, false, 0.5f);

	if (OutActors.Num() < 1) {
		return;
	}

	AActor* ClosestActor = OutActors[0];

	if (OutActors.Num() < 1) {

		// Finally iterate over the outActor array
		for (AActor* OverlappedActor : OutActors) {
			
			// For collision layers debugging
			//UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *OverlappedActor->GetName());

			// If actor not have interface 
			InteractionInterface = Cast<IIInteractable>(OverlappedActor);

			// Go to next iteration
			if (!InteractionInterface) {
				continue;
			}

			// If have interface check for closest distance
			if (GetSquaredDistanceTo(OverlappedActor) < GetSquaredDistanceTo(ClosestActor)) {
				ClosestActor = OverlappedActor;
			}
		}
	}
	// Before changing interacting actor
	if (InteractionInterface) {
		// Currently reset pointer
		InteractionInterface = nullptr;
	}

	InteractionInterface = Cast<IIInteractable>(ClosestActor);
	
	if (InteractionInterface) {
		InteractableActor = ClosestActor;
	}
}
