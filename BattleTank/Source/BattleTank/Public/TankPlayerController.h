// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAmingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAmingComponent* AimCompRef);

public:

	
	
	virtual void BeginPlay() override;

private:

	virtual void Tick(float DeltaTime) override;

	//Start the tank moving the barrel so that a shot would hit where
	//the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocaton) const;


	bool GetLookVectorHitLocation(FVector& HitLocaton, FVector LookDirection) const;

	//
	bool GetLookDirection(FVector& LookDirection, FVector2D ScreenLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000.f;
};
