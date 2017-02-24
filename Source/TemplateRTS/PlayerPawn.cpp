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
	InputComponent->BindAction("ActionTwo", IE_Pressed, this, &APlayerPawn::ActionTwo);
}

void APlayerPawn::ActionOne()
{
	if (_playerController)
	{
		FVector location;
		FVector direction;
		
		_playerController->DeprojectMousePositionToWorld(location, direction);

		//location the PC is focused on
		const FVector Start = _mainCamera->GetComponentLocation();
		//1000 units in facing direction of PC (distanceActions cm in front of the camera)
		const FVector End = Start + (direction * 2000.0f);

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
			ClearSelectedUnit();
			if (HitInfo.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("hit action one !"));
				auto ai = Cast<AAIBase>(HitInfo.GetActor());
				if (ai)
				{
					_selection.Add(ai);
					ai->SetSelected(true);
				}
			}
		}
	}
}

void APlayerPawn::ActionTwo()
{
	if (_playerController)
	{
		FVector location;
		FVector direction;

		_playerController->DeprojectMousePositionToWorld(location, direction);

		//location the PC is focused on
		const FVector Start = _mainCamera->GetComponentLocation();
		//1000 units in facing direction of PC (distanceActions cm in front of the camera)
		const FVector End = Start + (direction * 2000.0f);

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
				UE_LOG(LogTemp, Warning, TEXT("hit action two !"));
				
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

