// Fill out your copyright notice in the Description page of Project Settings.

#include "TemplateRTS.h"
#include "PlayerPawn.h"
#include "AIBase.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = _sceneComponent;

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_springArm->SetupAttachment(_sceneComponent);

	_mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	_mainCamera->SetupAttachment(_springArm);

	actionLength = 3000.0f;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	_playerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ActionOne", IE_Pressed, this, &APlayerPawn::ActionOne);
	InputComponent->BindAction("ActionOne", IE_Released, this, &APlayerPawn::FinishActionOne);
	InputComponent->BindAction("ActionTwo", IE_Pressed, this, &APlayerPawn::ActionTwo);
}

void APlayerPawn::ActionOne()
{
	if (_playerController)
	{
		FVector location;
		FVector direction;
		
		_playerController->DeprojectMousePositionToWorld(location, direction);

		const FVector Start = _mainCamera->GetComponentLocation();
		const FVector End = Start + (direction * actionLength);

		_playerController->GetMousePosition(_lastMousePos.X, _lastMousePos.y);

		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		QParams.AddIgnoredActor(this);
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

		DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(255, 0, 0),
		true, -1, 0,
		1
		);

		_selectionSuccess = false;

		if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, Channel, QParams))
		{
			if (HitInfo.GetActor())
			{
				auto ai = Cast<AAIBase>(HitInfo.GetActor());
				if (ai)
				{
					_selectionSuccess = true;
					ClearSelectedUnit();
					_selection.Add(ai);
					ai->SetSelected(true);
				}
			}
		}
	}
}

void APlayerPawn::FinishActionOne()
{
	if (!_selectionSuccess)
	{
		ClearSelectedUnit();

	}

}

void APlayerPawn::ActionTwo()
{
	if (_playerController)
	{
		FVector location;
		FVector direction;

		_playerController->DeprojectMousePositionToWorld(location, direction);

		const FVector Start = _mainCamera->GetComponentLocation();
		const FVector End = Start + (direction * actionLength);

		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		QParams.AddIgnoredActor(this);
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor(255, 0, 0),
			true, -1, 0,
			1
		);

		if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, Channel, QParams))
		{
			if (HitInfo.GetActor())
			{
				if (_selection.Num() > 0)
				{
					for (auto i = 0; i < _selection.Num(); i++)
					{
						_selection[i]->MoveUnit(HitInfo.Location);
					}
				}
			}
		}
	}
}

void APlayerPawn::ClearSelectedUnit()
{
	for (auto i = 0; i < _selection.Num(); i++)
	{
		_selection[i]->SetSelected(false);
	}
	_selection.Empty();
}

