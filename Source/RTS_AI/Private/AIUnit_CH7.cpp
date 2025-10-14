#include "AIUnit_CH7.h"

#include "RTS_AI/HealthComponent.h"

AAIUnit_CH7::AAIUnit_CH7()
{
	_HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void AAIUnit_CH7::Init()
{
	_HealthComp->onComponentDead.AddDynamic(this, &AAIUnit_CH7::Handle_HealthDeath);
}

void AAIUnit_CH7::Handle_HealthDeath(AController* causer)
{
	onUnitDeath.Broadcast(causer, _PointValue);
	Destroy();
}