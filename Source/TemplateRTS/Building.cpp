// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "Building.h"
#include "PlayerPawn.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABuilding::SetPlayerOwner(APlayerPawn* APlayerOwner)
{
	_playerOwner = APlayerOwner;
	_teamNumber = APlayerOwner->GetTeamNumber();
}