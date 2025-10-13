#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIUnit_CH7.generated.h"

class UHealthComponent;


UCLASS(Abstract)
class RTS_AI_API AAIUnit_CH7 : public APawn
{
	GENERATED_BODY()

public:
	AAIUnit_CH7();
	void Init();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr <UHealthComponent> _HealthComp;
	UFUNCTION()
	void Handle_HealthDeath(AController* causer);
// protected:
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	int _PointValue;
};