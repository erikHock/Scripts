// Fill out your copyright notice in the Description page of Project Settings.


#include "Bobber.h"


// Sets default values
ABobber::ABobber() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetRotation = GetActorRotation();
		
}



// Called when the game starts or when spawned
void ABobber::BeginPlay()
{
	Super::BeginPlay();

	// Trajectory Timer Setup//
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("TrajectoryUpdate"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("OnBobberArrived"));
	
	TrajectoryTimeline.AddInterpFloat(TrajectoryCurve, ProgressUpdate);
	TrajectoryTimeline.SetTimelineFinishedFunc(FinishedEvent);

	// Floating Timer Setup //
	FOnTimelineFloat FloatingUpdate;
	FloatingUpdate.BindUFunction(this, FName("FloatingMovementUpdate"));

	FloatingMovementTimeline.SetLooping(true);
	FloatingMovementTimeline.AddInterpFloat(FloatingMovementCurve, FloatingUpdate);
	
}

// Called every frame
void ABobber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TrajectoryTimeline.TickTimeline(DeltaTime);
	FloatingMovementTimeline.TickTimeline(DeltaTime);

}

void ABobber::PlayTimlineTrajectory(FVector PathDestination) {
	SetDestination(PathDestination);
	TrajectoryTimeline.PlayFromStart();
}

void ABobber::TrajectoryUpdate(float Alpha) {
	FVector NewLocation = FMath::Lerp(GetActorLocation(), Destination, Alpha);

	// Creating arch in trajectory
	NewLocation.Z += TrajectoryHeight * sin(Alpha * FMathf::Pi);

	SetActorLocation(NewLocation);
}

void ABobber::FloatingMovementUpdate(float Alpha) {
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = FloatingZOffset * Alpha;
	SetActorLocation(NewLocation);


	if (GetActorRotation().Equals(TargetRotation, 1.0f)){  
		TargetRotation = FRotator(FMath::RandRange(-30.0f,30.0f), FMath::RandRange(-30.0f, 30.0f), 0.0f);
	}

	FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRotation, Alpha, 0.03f);
	SetActorRotation(NewRot);
}

void ABobber::OnBobberArrived() {
	PlayTimlineFloating(true);
}

void ABobber::PlayTimlineFloating(bool bEnable) {
	if (bEnable) {
		FloatingMovementTimeline.PlayFromStart();
	}
	else {
		FloatingMovementTimeline.Stop();
	}


}

