// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "AAudioEventController.generated.h"

class UQuartzSubsystem;
class UQuartzClockHandle;
class UAudioComponent;
class FOnQuartzCommandEvent;
class FOnQuartzMetronomeEventBP;
class UUEventBus;
class AThridPShooterGameMode;
class UUW_HUD;
class ACore_HUD;

UCLASS()
class THRIDPSHOOTER_API AAAudioEventController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAudioEventController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AudioEventController")
	void StartBeat();
	
	/** Difference between engine and quartz time in miliseconds */
	UFUNCTION()
	float GetTimeDifferenceInMS(float& Time, float& AnotherTime);

	/** Component where is music played */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<UAudioComponent> AudioComponent;

	/** BPM of music */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float BPM = 60.0;

	/** Starting beat time offset in miliseconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float StartBeatTimeOffset = 0.2f;

	UPROPERTY(BlueprintReadOnly, Category = "AudioEventController")
	bool bIsSetupComplete = false;
	
private:
	/** Clock Start Time - World Time before */
	UFUNCTION()
	float GetOffsetedTimeWithStartInSeconds();

	/** Metronome binded Event tigger every x beat */ 
	UFUNCTION()
	void OnBeatEvent(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);

	UFUNCTION()
	void OnBeatStarted(EQuartzCommandDelegateSubType EventType, FName name);

	UPROPERTY()
	FOnQuartzMetronomeEventBP QuartzMetronomeEvent;

	UPROPERTY()
	FOnQuartzCommandEventBP QuartzCommandEvent;

	UPROPERTY()
	TObjectPtr<UQuartzSubsystem> QuartzSubsystem;

	UPROPERTY()
	UQuartzClockHandle* ClockHandle;

	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	FQuartzQuantizationBoundary QuantizationBoundary;

	UPROPERTY()
	float TimespanBeforePlay = 0.0f;

	UPROPERTY()
	float BeatCurrentTimespan = 0.0f;

	UPROPERTY()
	UUEventBus* EventBus = nullptr;

	UPROPERTY()
	bool CanTick = false;

	UPROPERTY()
	int32 CurrentBeat = 0;

	UPROPERTY()
	int32 TriggeredBeat = 0;

	UPROPERTY()
	bool bIsTickedCurrentFrame = false;
};
