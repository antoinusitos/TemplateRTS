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

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _timeToEarn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	int _amountEarn;

private:

	float _currentTimeToEarn;
};
