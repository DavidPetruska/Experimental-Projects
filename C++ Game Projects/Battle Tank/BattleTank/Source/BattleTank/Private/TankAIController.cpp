// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponet.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AimingComponet = GetPawn()->FindComponentByClass<UTankAimingComponet>();
	auto* ControlledTank = GetPawn();
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponet->AimAt(PlayerTank->GetActorLocation());
	}

	if (AimingComponet->GetFiringState() == EFiringState::Locked)
		AimingComponet->Fire();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedDeath);
	}
}

void ATankAIController::OnPossessedDeath()
{
	if (!ensure(GetPawn())) { return; } // TODO remove if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}