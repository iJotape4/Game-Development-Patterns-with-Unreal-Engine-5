#include "GuardTower_CH5_1.h"

#include "EliteUnit.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void AGuardTower_CH5_1::Handle_RotateLight_Update(float val)
{
	_LightPivot->SetRelativeRotation(
		FRotator(0.f, FMath::Lerp(-40.f, 40.f, val), 0.f)
		);
}

void AGuardTower_CH5_1::Handle_RotateLight_Finished()
{
	_RotateForward = !_RotateForward;
	StartRotation();
}

void AGuardTower_CH5_1::StartRotation()
{
	if(_RotateForward)
	{
		T_RotateLight->Play();
	}
	else
	{
		T_RotateLight->Reverse();
	}
}

void AGuardTower_CH5_1::StopRotation()
{
	T_RotateLight->Stop();
}

AGuardTower_CH5_1::AGuardTower_CH5_1()
{
	PrimaryActorTick.bCanEverTick = true;
	_RotateForward = true;
	_EnemySpotted = false;
	_DetectionRange = 4000.f;
	_DetectionRadius = 250.f;

	_TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = _TowerMesh;
	
	_LightPivot = CreateDefaultSubobject<USceneComponent>(TEXT("LightPivot"));
	_LightPivot->SetupAttachment(_TowerMesh);
	
	_LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	_LightMesh->SetupAttachment(_LightPivot);
	
	_SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	_SpotLight->SetupAttachment(_LightMesh);
	
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_LightMesh);

	 _Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	_Sphere->SetupAttachment(_LightMesh);
	_Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGuardTower_CH5_1::OnSphereOverlapBegin);
	_Sphere->OnComponentEndOverlap.AddDynamic(this, &AGuardTower_CH5_1::OnSphereOverlapEnd);

	T_RotateLight = CreateDefaultSubobject<UTimelineComponent>(TEXT("T_RotateLight"));
	onTimeline_Update.BindUFunction(this, FName("Handle_RotateLight_Update"));
	onTimeline_Finished.BindUFunction(this, FName("Handle_RotateLight_Finished"));
}


void AGuardTower_CH5_1::BeginPlay()
{
	Super::BeginPlay();

	if (_Curve == nullptr) { return; }
	T_RotateLight->AddInterpFloat(_Curve, onTimeline_Update, FName("Alpha"));
	T_RotateLight->SetTimelineFinishedFunc(onTimeline_Finished);
	T_RotateLight->SetLooping(false);
	T_RotateLight->SetIgnoreTimeDilation(true);
	StartRotation();
}

void AGuardTower_CH5_1::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (_EnemyUnit != nullptr) { return; }

	_EnemyUnit = Cast<AEliteUnit> (OtherActor);
	
	//If the cast fails, returns a nullptr
	if (_EnemyUnit == nullptr) { return; }
	
	FHitResult hit(ForceInit);
	FVector start = _Arrow->GetComponentLocation();
	FVector end = _EnemyUnit->GetActorLocation();

	//performs a line trace (raycast) from start to end in the game world,
	//ignoring the _EnemyUnit actor.
	//It uses Unreal Engine's UKismetSystemLibrary::LineTraceSingle
	//to check if there is a clear line of sight between the guard
	//tower and the enemy unit. If the trace hits something (i.e., the line is blocked),
	//the function returns early 
	if (UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), start, end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, {_EnemyUnit},
		EDrawDebugTrace::ForDuration, hit, true,
		FLinearColor::Red, FLinearColor::Green, 0.5f))
	{return;}

	_EnemySpotted = true;
	StopRotation();
}

void AGuardTower_CH5_1::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_EnemySpotted = false;
	_EnemyUnit = nullptr;
	StartRotation();
}


