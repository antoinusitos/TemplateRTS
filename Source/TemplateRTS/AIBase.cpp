// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "AIBase.h"
#include "BaseAIController.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();

	_selected = false;
	_theController = GetWorld()->SpawnActor<ABaseAIController>(controllerToSpawn, FVector::ZeroVector, FRotator::ZeroRotator);
	_theController->Possess(this);
}

// Called every frame
void AAIBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAIBase::SetSelected(bool newSelection)
{
	_selected = newSelection;
}

ABaseAIController* AAIBase::GetController()
{
	return _theController;
}

void AAIBase::MoveUnit(const FVector& location)
{
	if (_theController)
	{
		_theController->MoveToLocation(location, 0.5f);
	}
}

