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

UENUM(BlueprintType)
enum class EBuildingEnum : uint8
{
	None 		UMETA(DisplayName = "None"),
	Mine	 	UMETA(DisplayName = "Mine"),
	Barracks 	UMETA(DisplayName = "Barracks"),
	Base		UMETA(DisplayName = "Base"),
};

UENUM(BlueprintType)
enum class EPlayerStateEnum : uint8
{
	None 		UMETA(DisplayName = "None"),
	Moving	 	UMETA(DisplayName = "Moving"),
	Placing 	UMETA(DisplayName = "Placing"),
};

UENUM(BlueprintType)
enum class EBuildingStateEnum : uint8
{
	None 		UMETA(DisplayName = "None"),
	Building	UMETA(DisplayName = "Building"),
	Placed	 	UMETA(DisplayName = "Placed"),
};