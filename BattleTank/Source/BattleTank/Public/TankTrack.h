// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"



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

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void ApplySidewaysForce();

	void DriveTrack();

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDirningForce = 40000000.0f;
	

	float CurrentThrottle = 0;
};
