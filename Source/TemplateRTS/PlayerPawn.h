// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class AAIBase;

UCLASS()
class TEMPLATERTS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	USceneComponent* _sceneComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	USpringArmComponent* _springArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	UCameraComponent* _mainCamera;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float actionLength;

private:

	void ActionOne();
	void FinishActionOne();

	void ActionTwo();
	
	void ClearSelectedUnit();

private:
	
	bool _selectionSuccess;

	FVector _lastMousePos;

	APlayerController* _playerController;

	TArray<AAIBase*> _selection;

};
