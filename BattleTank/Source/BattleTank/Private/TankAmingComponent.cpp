// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAmingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"


void UTankAmingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAmingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel))
	{
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	/// Calculate The Velocity with startLocation endLocation startSpeed 
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{

	}
	
}
void UTankAmingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret)
	{
		return;
	}

	//Work difference between current rotation, and AimDeriction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Elevate(DeltaRotator.Yaw);
}

