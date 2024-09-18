// Fill out your copyright notice in the Description page of Project Settings.


#include "AAudioEventController.h"
#include "Quartz/QuartzSubsystem.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "Components/AudioComponent.h"
#include "Sound/QuartzQuantizationUtilities.h"
#include <ThridPShooter/Proxy/UEventBus.h>
#include <ThridPShooter/Core/ThridPShooterGameMode.h>
#define DEBUG_ON_SCREEN

// Sets default values
AAAudioEventController::AAAudioEventController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AAAudioEventController::BeginPlay() {
	Super::BeginPlay();

	World = GetWorld();

	// Get and cache event bus from Game Mode
	AThridPShooterGameMode* GM = Cast<AThridPShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	EventBus = GM->GetEventBus();

	// Create Quartz and Setup dependencies
	QuartzSubsystem = UQuartzSubsystem::Get(World);

	FQuartzTimeSignature TimeSignature = FQuartzTimeSignature();
	TimeSignature.NumBeats = 4;
	TimeSignature.BeatType = EQuartzTimeSignatureQuantization::QuarterNote;

	FQuartzClockSettings ClockSettings = FQuartzClockSettings(TimeSignature, false);

	ClockHandle = QuartzSubsystem->CreateNewClock(World, FName("MainClock"), ClockSettings, false, true);

	QuantizationBoundary = FQuartzQuantizationBoundary(EQuartzCommandQuantization::Beat, 1.0, EQuarztQuantizationReference::BarRelative);
	ClockHandle->SetBeatsPerMinute(World, QuantizationBoundary, QuartzCommandEvent, ClockHandle, BPM);

	// Trigger every beat
	QuartzMetronomeEvent.BindUFunction(this, FName("OnBeatEvent"));
	
	ClockHandle->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Beat, QuartzMetronomeEvent, ClockHandle );

	bIsSetupComplete = true;
	
}

// Called every frame
void AAAudioEventController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CanTick) { return; }

	// Main EVENT for Spawning HUD Widgets
	// We need calculate time before beat for spawn image in widget
	// If beat time >= offseted beat time
	if (!bIsTickedCurrentFrame)
	{
		float OffsetedTime = GetOffsetedTimeWithStartInSeconds();

		if (OffsetedTime >= BeatCurrentTimespan - StartBeatTimeOffset && TriggeredBeat != CurrentBeat) { 
			float Duration = BeatCurrentTimespan - (BeatCurrentTimespan - StartBeatTimeOffset);
			
			// If event not triggered this beat
			TriggeredBeat = CurrentBeat;
			// Trigger it this frame
			EventBus->OnBeatEventHUD.Broadcast(Duration, OffsetedTime);
			bIsTickedCurrentFrame = true;
		}
		
	}

	if (bIsTickedCurrentFrame)
	{
		bIsTickedCurrentFrame = false;
	}


}

// Binded function for start clock after QuartzCommandEvend qeued audio
void AAAudioEventController::StartBeat() {
	ensureMsgf(bIsSetupComplete == true, TEXT("Quartz setup not completed!"));	

	QuartzCommandEvent.BindUFunction(this, FName("OnBeatStarted"));
	AudioComponent->PlayQuantized(World, ClockHandle, QuantizationBoundary, QuartzCommandEvent, 0.0, 0.0, 1.0, EAudioFaderCurve::Linear);
	CanTick = true;

#ifdef DEBUG_ON_SCREEN
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Quartz Audio Started!"));
#endif

}

float AAAudioEventController::GetTimeDifferenceInMS(float& Time, float& AnotherTime) {
	float T1 = Time;
	float T2 = AnotherTime;
	float Difference = 0.0f;

	if (T1 > T2) {
		Difference = (T1 - T2) * 1000.0f;
	}
	else {
		Difference = (T2 - T1) * 1000.0f;
	}
	
	return Difference;
}

float AAAudioEventController::GetOffsetedTimeWithStartInSeconds() {
	float Time = World->GetTimeSeconds();
	float Offset = TimespanBeforePlay;

	return Time - Offset;
}

void AAAudioEventController::OnBeatEvent(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction) {
	FQuartzTransportTimeStamp TimeStamp = ClockHandle->GetCurrentTimestamp(World);
	BeatCurrentTimespan = TimeStamp.Seconds;
	CurrentBeat = Beat;

/* Debug latency of engine / audio engine
 * in miliseconds
 */
#ifdef DEBUG_ON_SCREEN
	float WorldSec = GetOffsetedTimeWithStartInSeconds();
	float TimeDiffInMS = GetTimeDifferenceInMS(WorldSec, TimeStamp.Seconds);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("BeatTime / WorldTime difference: %.2f"), TimeDiffInMS));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Beat: %d"), Beat));
#endif
}

void AAAudioEventController::OnBeatStarted(EQuartzCommandDelegateSubType EventType, FName name) {
	if (EventType == EQuartzCommandDelegateSubType::CommandOnQueued) {
		ClockHandle->StartClock(World, ClockHandle);
		TimespanBeforePlay = World->GetTimeSeconds();
	}
}

