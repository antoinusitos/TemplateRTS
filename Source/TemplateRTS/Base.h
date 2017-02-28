// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building.h"
#include "Base.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLATERTS_API ABase : public ABuilding
{
	GENERATED_BODY()
	
public:

	ABase();

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
		float _timeToEarn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
		int _amountEarn;

private:

	float _currentTimeToEarn;
	
	
};
