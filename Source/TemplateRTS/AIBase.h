// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Data.h"
#include "AIBase.generated.h"

class ABaseAIController;

UCLASS()
class TEMPLATERTS_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSelected(bool newSelection);

	ABaseAIController* GetController();

	void MoveUnit(const FVector& location);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TemplateRTS")
	TSubclassOf<ABaseAIController> controllerToSpawn;

	UFUNCTION(BlueprintImplementableEvent, Category = "TemplateRTS")
	void ToggleSelectionFeebackVisibility(bool mustBeActive);

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	int GetTeamNumber();
	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	void SetTeamNumber(int newTeam);

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	EUnitTypeEnum GetUnitType();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
	int GetCost();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TemplateRTS")
	int _teamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TemplateRTS")
	int _cost;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UStaticMeshComponent* _selectionFeedback;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TemplateRTS")
	EUnitTypeEnum _unitType;

	bool _selected;

	ABaseAIController* _theController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _timeToConstruct;
	float _currentTimeToConstruct;
};
