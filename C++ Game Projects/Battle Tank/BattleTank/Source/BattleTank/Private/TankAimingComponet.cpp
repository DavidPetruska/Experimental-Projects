// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponet.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponet::UTankAimingComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponet::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();

}
void UTankAimingComponet::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadInSeconds)
		FiringState = EFiringState::Reloading;
	else if (IsBarrelMoving() && AmmoCount > 0)
		FiringState = EFiringState::Aiming;
	else if (AmmoCount <= 0)
		FiringState = EFiringState::OutOfAmmo;
	else
		FiringState = EFiringState::Locked;


}

void UTankAimingComponet::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponet::AimAt(FVector HitLocation)
{
	if (!Barrel || !Turret)
		return;

	auto TankName = GetOwner()->GetName();
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
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
		)
		)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else return;
}

bool UTankAimingComponet::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01);
}

void UTankAimingComponet::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->RotateTurret(DeltaRotator.Yaw);
	else
		Turret->RotateTurret(-DeltaRotator.Yaw);
}

EFiringState UTankAimingComponet::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponet::Fire()
{
	if (FiringState == EFiringState::Reloading || FiringState == EFiringState::OutOfAmmo)
		return;
	else
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoCount--;
	}
}

int UTankAimingComponet::GetRoundsLeft() const
{
	return AmmoCount;
}