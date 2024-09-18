// Fill out your copyright notice in the Description page of Project Settings.


#include "ABaseWeapon.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "DA_WeaponData.h"

// Sets default values
AABaseWeapon::AABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

}


// Called when the game starts or when spawned
void AABaseWeapon::BeginPlay() {
	Super::BeginPlay();

	// Cache player reference
	PlayerActorRef = GetWorld()->GetFirstPlayerController();
}

void AABaseWeapon::Shoot() {
	// Raycasting to forward center of screen 
	FHitResult* Hit = new FHitResult();
	FVector Forward = PlayerActorRef->PlayerCameraManager->GetActorForwardVector();
	FVector Start = PlayerActorRef->PlayerCameraManager->GetCameraLocation();
	FVector End = (Forward * 1000.0f) + Start;
	
	FCollisionQueryParams* Col = new FCollisionQueryParams();
	Col->AddIgnoredActor(this);
	Col->AddIgnoredActor(PlayerActorRef);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);
	
	if (GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility, *Col)) {
		if (Hit->GetActor() != NULL) {
			UE_LOG(LogClass, Log, TEXT("Component: %s"), *Hit->GetComponent()->GetName());
			SpawnImpactEffect(Hit, Start);
		}
	}

	OnShootFired.Broadcast();
}

bool AABaseWeapon::Use_Implementation() {
	Shoot();
	return false;
}

// Called every frame
void AABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABaseWeapon::SpawnImpactEffect(FHitResult* HitReslut, FVector& StartPos) {
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(HitReslut->Location, StartPos);
	
	FVector Direction = (StartPos - HitReslut->Location);

	UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, HitReslut->Location, Rotation, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
	SpawnedEffect->SetNiagaraVariablePosition(FString("ConeAxis"), Direction);
	
	
	//Spawn Decal with some object pool with Timer
}
