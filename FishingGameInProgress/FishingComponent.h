// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FishingComponent.generated.h"

enum ECollisionChannel;
class ABobber;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCastLine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBobberSpawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReleaseCastedLine);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISHING_API UFishingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFishingComponent();

	/** Checking for water with line trace */
	UFUNCTION()
	bool IsWater(FVector& OutImpactPoint);

	UFUNCTION(BlueprintCallable, Category = "Fishing")
	void SpawnBobber();

	/** If casted line is released */
	UFUNCTION()
	void ReleaseCurrentCastedLine();

	/** Line Trace Collision Channel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UFUNCTION()
	void TryCastLine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing")
	TSubclassOf<ABobber> BobberClass;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = "Fishing")
	FOnCastLine OnCastLine;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = "Fishing")
	FOnBobberSpawn OnBobberSpawn;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, Category = "Fishing")
	FOnReleaseCastedLine OnReleaseCastedLine;
	
private:
	
	UPROPERTY()
	FVector WaterImpactPoint;

	UPROPERTY()
	TObjectPtr<ABobber> BobberRef;

	UPROPERTY()
	TObjectPtr<APlayerCameraManager> CamManager;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
