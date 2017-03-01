// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "Building.h"
#include "PlayerPawn.h"
#include "AIPeasant.h"
#include "Kismet/KismetMathLibrary.h"

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

	_rallyPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("RallyPoint"));
	_rallyPoint->SetupAttachment(_sceneComponent);

	_detectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Sphere"));
	_detectionSphere->SetupAttachment(_sceneComponent);

	_detectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OnBeginOverlap);

	_ProgressBar = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Progress Bar"));
	_ProgressBar->SetupAttachment(_sceneComponent);

	_cost = 100;
	_buildingState = EBuildingStateEnum::None;
	_buildingType = EBuildingEnum::None;
	_timeToConstruct = 5.0f;
	_currentTimeToConstruct = 0.0f;
	_canSpawn = true;
	_isSelected = false;
	_life = 100;
	_SpawnerOfUnit = false;

	_staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABuilding::Tick(float DeltaSeconds)
{
	if (_buildingState == EBuildingStateEnum::Building)
	{
		_currentTimeToConstruct += DeltaSeconds;
		if (_isSelected)
		{
			float diff = (_currentTimeToConstruct / _timeToConstruct) * 100;
			FString s = FString::FromInt(FMath::FloorToInt(diff)) + "%";
			_ProgressBar->SetText(FText::FromString(s));
			
		}

		if (_currentTimeToConstruct >= _timeToConstruct)
		{
			_ProgressBar->SetHiddenInGame(true);
			SetPlacedMaterial();
			if (_constructor)
			{
				_constructor->OutOfBuilding();
			}
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

void ABuilding::SetPeasantConstructor(AAIPeasant* theConstructor)
{
	_constructor = theConstructor;
}

void ABuilding::SetArrowComponentPosition(const FVector& newPos)
{
	_rallyPoint->SetWorldLocation(FVector(newPos.X, newPos.Y, _rallyPoint->GetComponentLocation().Z));
}

void ABuilding::SetSelected(bool newState)
{
	_isSelected = newState;
	if (_isSelected && _buildingState == EBuildingStateEnum::Building)
	{
		_ProgressBar->SetHiddenInGame(false);
	}

	if (_isSelected && _SpawnerOfUnit)
	{
		_rallyPoint->SetHiddenInGame(false);
	}
	else
	{
		_rallyPoint->SetHiddenInGame(true);
		_ProgressBar->SetHiddenInGame(true);
	}
}

void ABuilding::SetPlayerOwner(APlayerPawn* APlayerOwner)
{
	_playerOwner = APlayerOwner;
	_teamNumber = APlayerOwner->GetTeamNumber();
}

void ABuilding::SetWaitingMaterial()
{
	_staticMesh->SetMaterial(0, _waitingMaterial);
	_staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_buildingState = EBuildingStateEnum::Waiting;
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

void ABuilding::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_buildingState == EBuildingStateEnum::Waiting)
	{
		_constructor = Cast<AAIPeasant>(OtherActor);
		if (_constructor)
		{
			_constructor->MoveUnit(_constructor->GetActorLocation());
			_constructor->HideInBuilding(this);
			SetBuildingMaterial();
		}
	}
}