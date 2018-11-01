// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAmingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	///TODO
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControllerTank = GetPawn();

	if (!ensure(PlayerTank && ControllerTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControllerTank->FindComponentByClass<UTankAmingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
	

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (!ensure(InPawn)) { return; }
	else
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)){ return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}
void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn()))
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}