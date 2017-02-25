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

	_currentSelectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("box selection"));

	actionLength = 3000.0f;
	_executingActionOne = false;
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

	if (_executingActionOne)
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

		/*DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor(255, 0, 0),
			true, -1, 0,
			1
			);*/

		if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, Channel, QParams))
		{
			MakeSquareSelection(HitInfo.ImpactPoint);
		}
	}
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

		_executingActionOne = true;
		_currentSelectionBox->SetHiddenInGame(false);

		FHitResult HitInfo;
		FCollisionQueryParams QParams;
		QParams.AddIgnoredActor(this);
		ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
		FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

		/*DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(255, 0, 0),
		true, -1, 0,
		1
		);*/

		if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, Channel, QParams))
		{
			if (HitInfo.GetActor())
			{
				_lastMousePos = HitInfo.ImpactPoint;

				auto ai = Cast<AAIBase>(HitInfo.GetActor());
				if (ai)
				{
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
	_currentSelectionBox->SetHiddenInGame(true);
	_executingActionOne = false;
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

		/*DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor(255, 0, 0),
			true, -1, 0,
			1
		);*/

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

void APlayerPawn::MakeSquareSelection(const FVector& currentPos)
{

	FVector midPoint((_lastMousePos.X + currentPos.X) / 2.0f, (_lastMousePos.Y + currentPos.Y) / 2.0f, 50.0f);

	_currentSelectionBox->SetWorldLocation(midPoint);
	_currentSelectionBox->SetHiddenInGame(false);
	_currentSelectionBox->SetBoxExtent(FVector((currentPos.X - _lastMousePos.X) / 2, (currentPos.Y - _lastMousePos.Y)/2, 100.0f), true);

	TArray<AActor*> temp;
	_currentSelectionBox->GetOverlappingActors(temp, TSubclassOf<AAIBase>());

	ClearSelectedUnit();

	for (auto i = 0; i < temp.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("lol"));
		auto aiBase = Cast<AAIBase>(temp[i]);
		if (aiBase)
		{
			_selection.Add(aiBase);
		}
	}
}