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

	int GetCost();

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	USceneComponent* _sceneComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UStaticMeshComponent* _staticMesh;

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
};
