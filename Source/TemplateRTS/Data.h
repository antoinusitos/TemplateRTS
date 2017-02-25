#pragma once

#include "Data.generated.h"

UENUM(BlueprintType)
enum class EUnitTypeEnum : uint8
{
	None 		UMETA(DisplayName = "None"),
	Peasant 	UMETA(DisplayName = "Peasant"),
	Soldier 	UMETA(DisplayName = "Soldier"),
	Hero		UMETA(DisplayName = "Hero"),
	Ship		UMETA(DisplayName = "Ship"),
};

UENUM(BlueprintType)
enum class EAgesEnum : uint8
{
	None 		UMETA(DisplayName = "None"),
	WoodAge 	UMETA(DisplayName = "Wood Age"),
	SteelAge 	UMETA(DisplayName = "Steel Age"),
	SilverAge	UMETA(DisplayName = "Silver Age"),
	GoldAge		UMETA(DisplayName = "Gold Age"),
};