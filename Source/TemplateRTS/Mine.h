// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "Mine.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLATERTS_API AMine : public ABuilding
{
	GENERATED_BODY()
	
public:

	AMine();

	virtual void Tick(float DeltaSeconds) override;

private:

	float _timeToEarn;
	float _currentTimeToEarn;

	int _amountEarn;

	
};
