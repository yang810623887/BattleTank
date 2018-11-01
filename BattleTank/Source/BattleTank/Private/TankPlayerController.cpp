// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "TankAmingComponent.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAmingComponent>();
	if (!ensure(AimingComponent)) {	return;	}

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAmingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation;//Out parameter

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

//Get world location if linetrace through crosshair, true if hit Landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocaton) const
{
	AActor* MyPoint = GetOwner();
	HitLocaton = FVector(1.0f);

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(LookDirection, ScreenLocation))
	{
		if (GetLookVectorHitLocation(HitLocaton, LookDirection))
		{
			return true;
		}
		return false;
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocaton, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		/*DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			3.f
		);*/
		HitLocaton = HitResult.Location;
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection, FVector2D ScreenLocation ) const
{
	FVector CameraWorldLocation;//To be discarded
	if (DeprojectScreenPositionToWorld(
			ScreenLocation.X,
			ScreenLocation.Y,
			CameraWorldLocation,
			LookDirection
		))
	{
		return true;
	}
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (!ensure(InPawn)) { return; }
	else
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}
void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();

	//if (!ensure(GetPawn()))
	//{
	//	return;
	//}

	//GetPawn()->DetachFromControllerPendingDestroy();
}