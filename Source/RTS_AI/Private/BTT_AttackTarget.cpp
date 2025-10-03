// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_AttackTarget.h"

#include "GameplayTask.h"
#include "GameplayTasksComponent.h"
#include "GameFramework/Actor.h"

UGameplayTasksComponent* UBTT_AttackTarget::GetGameplayTasksComponent(const UGameplayTask& Task) const
{
	return nullptr;
}

AActor* UBTT_AttackTarget::GetGameplayTaskOwner(const UGameplayTask* Task) const
{
	return nullptr;
}

AActor* UBTT_AttackTarget::GetGameplayTaskAvatar(const UGameplayTask* Task) const
{
	return nullptr;
}

void UBTT_AttackTarget::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTT_AttackTarget::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

void UBTT_AttackTarget::OnGameplayTaskInitialized(UGameplayTask& Task)
{
}

