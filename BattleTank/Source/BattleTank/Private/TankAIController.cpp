// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	///TODO
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControllerTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("vectoring"));
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControllerTank->AimAt(PlayerTank->GetActorLocation());


		ControllerTank->Fire();
	}
	else
	{

	}
}
