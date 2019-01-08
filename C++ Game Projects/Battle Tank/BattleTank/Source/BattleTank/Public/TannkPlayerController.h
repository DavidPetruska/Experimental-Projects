// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TannkPlayerController.generated.h"

class UTankAimingComponet;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATannkPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponet* AimCompRef);
	
	UFUNCTION()
		void OnPossessedTankDeath();
private:
	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLoc = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLoc = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;
	void SetPawn(APawn * InPawn);
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
