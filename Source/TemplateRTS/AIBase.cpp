// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "AIBase.h"
#include "BaseAIController.h"
#include "Building.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_selectionFeedback = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selection Feedback"));
	_selectionFeedback->SetupAttachment(GetCapsuleComponent());

	_detection = CreateDefaultSubobject<USphereComponent>(TEXT("detection"));
	_detection->SetupAttachment(GetCapsuleComponent());
	_detection->OnComponentBeginOverlap.AddDynamic(this, &AAIBase::OnBeginOverlap);

	_unitType = EUnitTypeEnum::None;
	_teamNumber = -1;
	_cost = 50;
	_currentTimeToConstruct = 0.0f;
	_timeToConstruct = 2.0f;
	_canMove = true;
	_canAttack = true;
	_maxLife = 100;
	_life = _maxLife;
	_attack = 20;
	_cooldownAttack = 3.0f;
	_currentCooldown = 0.0f;
	_target = nullptr;
	_rangeAttack = 100.0f;
	_unitCanAttack = false;

	_detection->SetSphereRadius(600.0f);	

}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();

	_selected = false;
	if (controllerToSpawn)
	{
		_theController = GetWorld()->SpawnActor<ABaseAIController>(controllerToSpawn, FVector::ZeroVector, FRotator::ZeroRotator);
		_theController->Possess(this);
	}
}

void AAIBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float distToTarget = 99999;
	if (_target)
	{
		distToTarget = FVector::Dist(GetActorLocation(), _target->GetActorLocation());
	}

	if (_canAttack)
	{
		if (distToTarget <= _rangeAttack)
		{
			MoveUnit(GetActorLocation());
			_canAttack = false;
			_target->ReceiveHit(_attack);
		}
		else if (_target && distToTarget > _rangeAttack)
		{
			MoveUnit(_target->GetActorLocation());
		}
	}
	else
	{
		_currentCooldown += DeltaSeconds;
		if (_currentCooldown >= _cooldownAttack)
		{
			_currentCooldown = 0.0f;
			_canAttack = true;
		}

		if (_target && distToTarget > _rangeAttack)
		{
			MoveUnit(_target->GetActorLocation());
		}
		else if (_target && distToTarget <= _rangeAttack)
		{
			MoveUnit(GetActorLocation());
		}
	}
}

void AAIBase::SetSelected(bool newSelection)
{
	_selected = newSelection;
	ToggleSelectionFeebackVisibility(newSelection);
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

int AAIBase::GetTeamNumber()
{
	return _teamNumber;
}

void AAIBase::SetTeamNumber(int newTeam)
{
	_teamNumber = newTeam;
}

EUnitTypeEnum AAIBase::GetUnitType()
{
	return _unitType;
}

int AAIBase::GetCost()
{
	return _cost;
}

void AAIBase::HideInBuilding(ABuilding* theBuilding)
{
	SetActorHiddenInGame(true);
	_canMove = false;
	SetSelected(false);
}

void AAIBase::OutOfBuilding()
{
	SetActorHiddenInGame(false);
	_canMove = true;
}

bool AAIBase::GetCanMove()
{
	return _canMove;
}

bool AAIBase::ReceiveHit(int amount)
{
	_life -= amount;
	if (_life <= 0)
	{
		Destroy();
		return true;
	}
	return false;
}

void AAIBase::SetNewTarget(AAIBase* theTarget)
{
	_target = theTarget;
}

bool AAIBase::GetUnitCanAttack()
{
	return _unitCanAttack;
}

void AAIBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_unitCanAttack)
	{
		AAIBase* enemy = Cast<AAIBase>(OtherActor);
		if (enemy && enemy->GetTeamNumber() != _teamNumber && _target == nullptr)
		{
			_target = enemy;
		}
	}
}
