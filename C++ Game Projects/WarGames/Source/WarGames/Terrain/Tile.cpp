// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "../ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	minVector = FVector(0, -2000, 0);
	maxVector = FVector(4000, 2000, 0);
	NavigationBoundOffset = FVector(2000, 0, 0);

}

void ATile::SetPool(UActorPool* InPool)
{
	Pool = InPool;

	PositionNavMeshBoundVolume();
}

void ATile::PositionNavMeshBoundVolume()
{
	NavMeshBV = Pool->Checkout();
	if (NavMeshBV == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Actors find in the NavMeshBoundsVolume Pool."));
		return;
	}
	NavMeshBV->SetActorLocation(GetActorLocation() + NavigationBoundOffset);
	FNavigationSystem::Build(*GetWorld());
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 minSpawn, int32 maxSpawn, float Radius, float minScale, float maxScale)
{
	for (size_t i = 0; i < FMath::RandRange(minSpawn, maxSpawn); i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(minScale, maxScale);
		bool found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 minSpawn, int32 maxSpawn, float Radius, float minScale, float maxScale)
{
	RandomlyPlaceActors(ToSpawn, minSpawn, maxSpawn, Radius, minScale, maxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 minSpawn, int32 maxSpawn, float Radius)
{
	RandomlyPlaceActors(ToSpawn, minSpawn, maxSpawn, Radius, 1, 1);
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(AITag);
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	const int32 MAX_ATTEMPTS = 100;

	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidateLocation = FMath::RandPointInBox(FBox(minVector, maxVector));
		if (bCanSpawnAtLocation(CandidateLocation, Radius))
		{
			OutLocation = CandidateLocation;
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ATile::bCanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult hitResult;

	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		GlobalLocation,
		GlobalLocation+.0001f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));
	
	FColor resultColor = hasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, resultColor, true, 100);
	return !hasHit;
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(Pool != nullptr && NavMeshBV != nullptr)
		Pool->ReturnActor(NavMeshBV);
}