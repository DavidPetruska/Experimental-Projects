// Fill out your copyright notice in the Description page of Project Settings.

#include "TannkPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponet.h"


void ATannkPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATannkPlayerController::OnPossessedTankDeath);
	}
}


void ATannkPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


void ATannkPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponet = GetPawn()->FindComponentByClass<UTankAimingComponet>();
	if (AimingComponet)
		FoundAimingComponent(AimingComponet);
}

void ATannkPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATannkPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn()) return;
	auto AimingComponet = GetPawn()->FindComponentByClass<UTankAimingComponet>();
	if (!AimingComponet)
		return;
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
		AimingComponet->AimAt(HitLocation);

}

bool ATannkPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLoc, ViewportSizeY * CrossHairYLoc);	

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATannkPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWoldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWoldLocation, LookDirection);

}

bool ATannkPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
		return false;
}