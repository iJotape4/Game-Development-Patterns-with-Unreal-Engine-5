#include "BTT_AttackTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RTS_AI/EliteUnit.h"
#include "ControllableUnit.h" // Added for interface Execute_ calls

UGameplayTasksComponent* UBTT_AttackTarget::GetGameplayTasksComponent(const UGameplayTask& Task) const
{
	return Super::GetGameplayTasksComponent(Task);
}

AActor* UBTT_AttackTarget::GetGameplayTaskOwner(const UGameplayTask* Task) const
{
	return Super::GetGameplayTaskOwner(Task);
}

AActor* UBTT_AttackTarget::GetGameplayTaskAvatar(const UGameplayTask* Task) const
{
	return Super::GetGameplayTaskAvatar(Task);
}

void UBTT_AttackTarget::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTT_AttackTarget::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTT_AttackTarget::OnGameplayTaskInitialized(UGameplayTask& Task)
{
	Super::OnGameplayTaskInitialized(Task);
}

UBTT_AttackTarget::UBTT_AttackTarget()
{
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UBTT_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = OwnerComp.GetAIOwner();
	if (!AI) return EBTNodeResult::Failed;

	AEliteUnit* Elite = Cast<AEliteUnit>(AI->GetPawn());
	if (!Elite) return EBTNodeResult::Failed;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	UObject* TargetObj = BB->GetValueAsObject(TargetKey.SelectedKeyName);
	if (!TargetObj) return EBTNodeResult::Failed;

	// Use interface Execute_ method instead of calling the event directly to avoid assert.
	if (Elite->GetClass()->ImplementsInterface(UControllableUnit::StaticClass()))
	{
		IControllableUnit::Execute_AttackTarget(Elite, TargetObj);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_AttackTarget: %s does NOT implement ControllableUnit interface"), *Elite->GetName());
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
