// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void ElevateBarrel(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxEvalationDegs = 30.f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinEvatationDegs = 0.f;

	
};
