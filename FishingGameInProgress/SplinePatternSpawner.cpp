// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePatternSpawner.h"
#include "Components/SplineComponent.h"
#include "SplinePatternCollider.h"

// Sets default values
ASplinePatternSpawner::ASplinePatternSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplinePattern = CreateDefaultSubobject<USplineComponent>(FName(TEXT("Spline Pattern")));
	SetRootComponent(SplinePattern);
}

// Called when the game starts or when spawned
void ASplinePatternSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASplinePatternSpawner::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	if (SplinePattern && SplinePattern->GetNumberOfSplinePoints() > 0) {
		
		SplinePatternColliders.Empty();
		
		// Populate SplinePattern with Colliders
		for (int32 i = 0; i < SplinePattern->GetNumberOfSplinePoints() - 1; i++) {
			FTransform NewTransform;
			NewTransform.SetTranslation(SplinePattern->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));

			UActorComponent* Comp = AddComponentByClass(ASplinePatternCollider::StaticClass(), true, NewTransform, false);

			if (ASplinePatternCollider* Collider = Cast<ASplinePatternCollider>(Comp)) {
				SplinePatternColliders.Add(Collider);
			}

			/*ASplinePatternCollider* Collider = NewObject<ASplinePatternCollider>(this, ASplinePatternCollider::StaticClass(), FName(TEXT("Collider %d"), i));
			Collider->SetRootComponent(SplinePattern);
			Collider->SetActorLocation(SplinePattern->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
			SplinePatternColliders.Add(Collider);*/
		}
	}


}

// Called every frame
void ASplinePatternSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

