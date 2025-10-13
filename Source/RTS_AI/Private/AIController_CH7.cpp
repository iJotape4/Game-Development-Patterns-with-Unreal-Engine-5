#include "AIController_CH7.h"

#include "AIUnit_CH7.h"

void AAIController_CH7::Init()
{
	if (APawn* pawn = GetPawn())
	{
		if (_Unit = Cast<AAIUnit_CH7>(pawn))
			_Unit->Init();
	}
}
