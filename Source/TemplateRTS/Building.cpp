// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "Building.h"
#include "PlayerPawn.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = _sceneComponent;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_staticMesh->SetupAttachment(_sceneComponent);

	_arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	_arrowComponent->SetupAttachment(_sceneComponent);

	_cost = 100;
	_buildingState = EBuildingStateEnum::None;
	_buildingType = EBuildingEnum::None;
	_timeToConstruct = 5.0f;
	_currentTimeToConstruct = 0.0f;
	_canSpawn = true;

	_staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABuilding::Tick(float DeltaSeconds)
{
	if (_buildingState == EBuildingStateEnum::Building)
	{
		_currentTimeToConstruct += DeltaSeconds;
		if (_currentTimeToConstruct >= _timeToConstruct)
		{
			SetPlacedMaterial();
		}
	}
}

EBuildingEnum ABuilding::GetBuildingType()
{
	return _buildingType;
}

EBuildingStateEnum ABuilding::GetBuildingState()
{
	return _buildingState;
}

FVector ABuilding::GetSpawnPos()
{
	return _arrowComponent->GetComponentLocation();
}

FRotator ABuilding::GetSpawnRot()
{
	return _arrowComponent->GetComponentRotation();
}

int ABuilding::GetTeamNumber()
{
	return _teamNumber;
}

void ABuilding::AddUnitToSpawn(EUnitTypeEnum newUnitToSpawn)
{
	_unitsToSpawn.Add(newUnitToSpawn);
}

void ABuilding::SetPlayerOwner(APlayerPawn* APlayerOwner)
{
	_playerOwner = APlayerOwner;
	_teamNumber = APlayerOwner->GetTeamNumber();
}

int ABuilding::GetCost()
{
	return _cost;
}

void ABuilding::SetBuildingMaterial()
{
	_staticMesh->SetMaterial(0, _buildingMaterial);
	_staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_buildingState = EBuildingStateEnum::Building;
}

void ABuilding::SetPlacedMaterial()
{
	_staticMesh->SetMaterial(0, _baseMaterial);
	_buildingState = EBuildingStateEnum::Placed;
}