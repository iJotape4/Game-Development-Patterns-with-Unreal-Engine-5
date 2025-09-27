// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	_max_health = 100.f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	_current_health = _max_health;
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer)
{
	_current_health=FMath::Max(_current_health-damage, 0.f);
	OnComponentDamaged.Broadcast(instigator, damage, _current_health);
	if (_current_health <= 0.f)
	{
		OnComponentDead.Broadcast(instigator);
	}
}