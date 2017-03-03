// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Data.h"
#include "AIBase.generated.h"

class ABaseAIController;
class ABuilding;

UCLASS()
class TEMPLATERTS_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetSelected(bool newSelection);

	ABaseAIController* GetController();

	UFUNCTION(BlueprintCallable, Category = "TemplateRTS")
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

	void HideInBuilding(ABuilding* theBuilding);
	void OutOfBuilding();

	bool GetCanMove();

	bool ReceiveHit(int amount);

	void SetNewTarget(AAIBase* theTarget);

	bool GetUnitCanAttack();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TemplateRTS")
	int _teamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TemplateRTS")
	int _cost;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	UStaticMeshComponent* _selectionFeedback;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "TemplateRTS")
	USphereComponent* _detection;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TemplateRTS")
	EUnitTypeEnum _unitType;

	bool _selected;

	ABaseAIController* _theController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	UTexture2D* _unitImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _timeToConstruct;
	float _currentTimeToConstruct;

	bool _canMove;
	bool _canAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	int _life;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	int _maxLife;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	int _attack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _cooldownAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	AAIBase* _target;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	float _rangeAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TemplateRTS")
	bool _unitCanAttack;

private:

	float _currentCooldown;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
