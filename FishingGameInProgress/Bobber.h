// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Bobber.generated.h"

class UCurveFloat;

UCLASS()
class FISHING_API ABobber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABobber();

	UFUNCTION()
	void PlayTimlineFloating(bool bEnable);

	UFUNCTION()
	void PlayTimlineTrajectory(FVector PathDestination);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bobber")
	TObjectPtr<UCurveFloat> TrajectoryCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bobber")
	TObjectPtr<UCurveFloat> FloatingMovementCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bobber")
	float FloatingZOffset = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bobber")
	float TrajectoryHeight = 100.0f;


private:

	UFUNCTION()
	void SetDestination(FVector EndDestination) { Destination = EndDestination; };

	UFUNCTION()
	void TrajectoryUpdate(float Alpha);

	UFUNCTION()
	void FloatingMovementUpdate(float Alpha);

	UFUNCTION()
	void OnBobberArrived();

	FTimeline TrajectoryTimeline;

	FTimeline FloatingMovementTimeline;

	FVector Destination;

	FRotator TargetRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
