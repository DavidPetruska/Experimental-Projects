// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool;

UCLASS()
class WARGAMES_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "RNG")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, float Radius = 500, float minScale = 1, float maxScale = 1);	
	UFUNCTION(BlueprintCallable, Category = "RNG")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, float Radius = 500);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning Actors")
	FVector minVector;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning Actors")
	FVector maxVector;
	
	UPROPERTY(EditDefaultsOnly, Category = "NavMeshBound Alignment")
	FVector NavigationBoundOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bCanSpawnAtLocation(FVector Location, float Radius);
	
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	
	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 minSpawn = 1, int32 maxSpawn = 1, float Radius = 500, float minScale = 1, float maxScale = 1);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	void PositionNavMeshBoundVolume();

	UActorPool* Pool;
	AActor* NavMeshBV;
	FName AITag = "Guards";
};
