// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Bobber.h"
#define DEBUG_ENABLED

// Sets default values for this component's properties
UFishingComponent::UFishingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UFishingComponent::BeginPlay()
{
	Super::BeginPlay();

	CamManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	ensureMsgf(CamManager != nullptr, TEXT("CamManager empty pointer!"));
}


// Called every frame
void UFishingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UFishingComponent::IsWater(FVector& OutImpactPoint) {
	if (UWorld* World = GetWorld()) {


		FVector Start;
		FVector End;
		TArray<FHitResult> Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		Params.bTraceComplex = true;
		Params.bFindInitialOverlaps = true;
		FCollisionResponseParams ResponseParams;
	
		if (CamManager) {
			Start = CamManager->GetCameraLocation();
			End = Start + (CamManager->GetActorForwardVector() * 1000.0f);
		}

		if (World->LineTraceMultiByChannel(Hit, Start, End, CollisionChannel, Params, ResponseParams)) {
			if (Hit.Num() == 1) {
#ifdef DEBUG_ENABLED
				UE_LOG(LogTemp, Warning, TEXT("Water Hitted"));
				DrawDebugSphere(World, Hit[0].ImpactPoint, 10, 10, FColor::Green, false, 2.0f);
#endif
				OutImpactPoint = Hit[0].ImpactPoint;
				return true;
				
			}
			else {
#ifdef DEBUG_ENABLED
				UE_LOG(LogTemp, Warning, TEXT("Water IsNot Hitted"));
#endif
				OutImpactPoint = FVector(0, 0, 0);
				return false;
				
			}
		}
		

	}
	return false;
}

void UFishingComponent::SpawnBobber() {
	// SpawnParams Must be constructed in implementation
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();

	BobberRef = GetWorld()->SpawnActor<ABobber>(BobberClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	BobberRef->PlayTimlineTrajectory(WaterImpactPoint);
	OnBobberSpawn.Broadcast();
}

void UFishingComponent::ReleaseCurrentCastedLine() {
	BobberRef->PlayTimlineFloating(false);
	BobberRef->PlayTimlineTrajectory(GetOwner()->GetActorLocation());
	OnReleaseCastedLine.Broadcast();
}


void UFishingComponent::TryCastLine() {

	FVector ImpactP;
	if (IsWater(ImpactP)) {
		if (UWorld* World = GetWorld()) {
			
			// Check if facing to water
			float Dot = FVector::DotProduct(CamManager->GetActorForwardVector(), GetOwner()->GetActorForwardVector());
			if (Dot < 0.5f) {
				return;
			}
			
			WaterImpactPoint = ImpactP;
			OnCastLine.Broadcast();
		}
	}
}


