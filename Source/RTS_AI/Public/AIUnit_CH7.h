#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIUnit_CH7.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIUnitDeathSignature, AController*, causer, int, points);

UCLASS(Abstract)
class RTS_AI_API AAIUnit_CH7 : public APawn
{
	GENERATED_BODY()

public:
	AAIUnit_CH7();
	void Init();

	UPROPERTY(BlueprintAssignable)
	FAIUnitDeathSignature onUnitDeath;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr <UHealthComponent> _HealthComp;
	UFUNCTION()
	void Handle_HealthDeath(AController* causer);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointValue;
};