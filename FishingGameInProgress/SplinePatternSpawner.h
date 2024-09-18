// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePatternSpawner.generated.h"

class USplineComponent;
class ASplinePatternCollider;

UCLASS()
class FISHING_API ASplinePatternSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePatternSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplinePatternSpawner")
	TObjectPtr<USplineComponent> SplinePattern;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ASplinePatternCollider*> SplinePatternColliders;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
