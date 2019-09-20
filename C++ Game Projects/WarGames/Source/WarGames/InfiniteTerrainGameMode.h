// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarGamesGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WARGAMES_API AInfiniteTerrainGameMode : public AWarGamesGameMode
{
	GENERATED_BODY()
	

public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NMesh Pool")
	class UActorPool* NavMeshBV;

private:
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
};
