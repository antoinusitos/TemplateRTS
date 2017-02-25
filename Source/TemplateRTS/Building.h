// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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

protected:
	APlayerPawn* _playerOwner;

	int _teamNumber;
	
};
