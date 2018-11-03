// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "ConstructorHelpers.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Childrens;
	GetChildrenComponents(true, Childrens);
	for (USceneComponent* child : Childrens)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(child);
		if (!SpawnPointChild)
		{
			continue;
		}
		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnChild);
		if (!SprungWheel)
		{
			continue;
		}
		ResultArray.Add(SprungWheel);
	}
	
	return ResultArray;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
	
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDirningForce;
	
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	//UE_LOG(LogTemp, Warning, TEXT("%s : aaaaa %f"), *GetName(), ForcePerWheel)
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

	
}


