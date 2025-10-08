#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GuardTower_CH5_1.generated.h"

class UArrowComponent;
class USpotLightComponent;
UCLASS()
class RTS_AI_API AGuardTower_CH5_1 : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> _TowerMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> _LightPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> _LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USpotLightComponent> _SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UArrowComponent> _Arrow;

private:
	FOnTimelineFloat onTimeline_Update;
	FOnTimelineEventStatic onTimeline_Finished;

	UFUNCTION()
	void Handle_RotateLight_Update(float val);

	UFUNCTION()
	void Handle_RotateLight_Finished();

	void StartRotation();
	void StopRotation();


public:	
	// Sets default values for this actor's properties
	AGuardTower_CH5_1();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _RotateForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _EnemySpotted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _DetectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _DetectionRadius;

protected:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> T_RotateLight;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _Curve;
};
