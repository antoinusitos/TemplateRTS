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

	int GetTeamNumber();

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UStaticMeshComponent* _selectionFeedback;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TemplateRTS")
	EUnitTypeEnum _unitType;

	bool _selected;

	ABaseAIController* _theController;

	int _teamNumber;
};
