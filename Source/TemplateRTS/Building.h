// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Data.h"
#include "Building.generated.h"

class APlayerPawn;

UCLASS()
class TEMPLATERTS_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	void SetPlayerOwner(APlayerPawn* APlayerOwner);

	void SetBuildingMaterial();

	void SetPlacedMaterial();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	int GetCost();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	EBuildingEnum GetBuildingType();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	EBuildingStateEnum GetBuildingState();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	FVector GetSpawnPos();
	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	FRotator GetSpawnRot();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	int GetTeamNumber();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TemplateRTS")
	void SpawnPendingUnits();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	void AddUnitToSpawn(EUnitTypeEnum newUnitToSpawn);

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	USceneComponent* _sceneComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UStaticMeshComponent* _staticMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UArrowComponent* _arrowComponent;

	APlayerPawn* _playerOwner;

	int _teamNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	UMaterial* _buildingMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	UMaterial* _baseMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	int _cost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _timeToConstruct;
	float _currentTimeToConstruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	EBuildingStateEnum _buildingState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	EBuildingEnum _buildingType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	TArray<EUnitTypeEnum> _unitsToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	bool _canSpawn;

};
