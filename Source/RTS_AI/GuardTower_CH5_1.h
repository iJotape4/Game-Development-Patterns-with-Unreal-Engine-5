#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> _Sphere;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ACharacter> _EnemyUnit;

protected:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> T_RotateLight;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _Curve;

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
