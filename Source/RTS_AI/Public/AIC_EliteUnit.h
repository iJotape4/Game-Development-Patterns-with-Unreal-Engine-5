// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIC_EliteUnit.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AI_API AAIC_EliteUnit : public AAIController
{
	GENERATED_BODY()
public:
	AAIC_EliteUnit();

	// Behavior tree asset to run
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void OnPossess(APawn* InPawn) override;
};
