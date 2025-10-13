#include "PlayerController_Ch7.h"

#include "Character_CH7.h"
#include "Widget_Score_CH7.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerController_Ch7::Init()
{
	if (GetPawn()!= nullptr)
	{
		GetPawn()->Destroy();	
	}

	UWorld* const world = GetWorld();
	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLoc = tempStart != nullptr ? tempStart->GetActorLocation() : FVector::ZeroVector;
	FRotator spawnRot = tempStart != nullptr ? tempStart->GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* tempPawn = world->SpawnActor<APawn> (_PlayerPawn, spawnLoc, spawnRot, spawnParams);
	Possess(tempPawn);
	if (ACharacter_CH7* _Character = Cast<ACharacter_CH7>(tempPawn))
	{
		_Character->Init();
	}
	
	/*_ScoreWidget = CreateWidget<UWidget_Score_CH7, APlayerController_Ch7>(this, _ScoreWidgetClass.Get());
	_ScoreWidget->AddToViewport();*/
}