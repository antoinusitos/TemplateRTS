// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "Mine.h"
#include "PlayerPawn.h"

AMine::AMine()
{
	_timeToEarn = 1.0f;
	_currentTimeToEarn = 0.0f;
	_amountEarn = 100;
	_cost = 150;
}

void AMine::Tick(float DeltaSeconds)
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