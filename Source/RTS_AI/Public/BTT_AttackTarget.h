// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTaskOwnerInterface.h"
#include "BTT_AttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class RTS_AI_API UBTT_AttackTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// IGameplayTaskOwnerInterface
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;
	virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;
	UBTT_AttackTarget();

	// Blackboard key holding the target (Actor/Object)
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector TargetKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
