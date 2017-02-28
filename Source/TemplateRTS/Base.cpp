// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "Base.h"
#include "PlayerPawn.h"

ABase::ABase()
{
	_timeToEarn = 5.0f;
	_currentTimeToEarn = 0.0f;
	_amountEarn = 25;
	_cost = 10000;
}

void ABase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (_buildingState == EBuildingStateEnum::Placed)
	{
		_currentTimeToEarn += DeltaSeconds;
		if (_currentTimeToEarn >= _timeToEarn)
		{
			_currentTimeToEarn = 0.0f;
			if (_playerOwner)
				_playerOwner->EarnGold(_amountEarn);
		}
	}
}