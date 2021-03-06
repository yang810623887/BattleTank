// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

private:
	UTankTrack();

	TArray<ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDirningForce = 40000000.0f;
	

	
};
