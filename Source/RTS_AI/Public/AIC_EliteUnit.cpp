#include "AIC_EliteUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "RTS_AI/EliteUnit.h"

AAIC_EliteUnit::AAIC_EliteUnit()
{
	BehaviorTreeAsset = nullptr;
}

void AAIC_EliteUnit::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviorTreeAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("EliteAIController: BehaviorTreeAsset is not set!"));
		return;
	}

	UBlackboardComponent* BBComp = nullptr;
	if (UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BBComp))
	{
		RunBehaviorTree(BehaviorTreeAsset);

		AEliteUnit* Elite = Cast<AEliteUnit>(InPawn);
		if (Elite)
		{
			Elite->Init(BBComp);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EliteAIController: Failed to initialize Blackboard!"));
	}
}

