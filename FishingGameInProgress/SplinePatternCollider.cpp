// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePatternCollider.h"

// Sets default values
ASplinePatternCollider::ASplinePatternCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsHitted = false;
}

// Called when the game starts or when spawned
void ASplinePatternCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplinePatternCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

