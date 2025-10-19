// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_RTS.h"

#include "ControllableUnit.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APC_RTS::APC_RTS()
{
	_SelectedUnit = nullptr;
	_isQueueing = false;

	// Initialize Enhanced Input asset pointers to silence analyzer warnings
	InputMappingContext = nullptr;
	SelectAction = nullptr;
	ActionInput = nullptr;
	QueueAction = nullptr;
}

void APC_RTS::BeginPlay()
{
	Super::BeginPlay();

	// Register the Enhanced Input mapping context on the local player subsystem
	if(InputMappingContext && GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APC_RTS::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind Enhanced Input actions
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(SelectAction)
		{
			EnhancedInput->BindAction(SelectAction, ETriggerEvent::Triggered, this, &APC_RTS::Select);
		}

		if(ActionInput)
		{
			// Bind to Completed so it matches a release behavior
			EnhancedInput->BindAction(ActionInput, ETriggerEvent::Completed, this, &APC_RTS::ActionReleased);
		}

		if(QueueAction)
		{
			EnhancedInput->BindAction(QueueAction, ETriggerEvent::Triggered, this, &APC_RTS::StartQueueing);
			EnhancedInput->BindAction(QueueAction, ETriggerEvent::Completed, this, &APC_RTS::StopQueueing);
		}
	}

	bShowMouseCursor  = true;
}

void APC_RTS::Select(const FInputActionValue& Value)
{
	// Value unused — selection is done from cursor hit
	FHitResult traceResult;
	if(GetHitResultUnderCursorForObjects({UEngineTypes::ConvertToObjectType(ECC_Pawn)}, true, traceResult))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(traceResult.GetActor(), UControllableUnit::StaticClass()))
		{
			_SelectedUnit = traceResult.GetActor();
		}
	}
}

void APC_RTS::ActionReleased(const FInputActionValue& Value)
{
	if(!_SelectedUnit) return;
	
	FHitResult traceResult;
	if(!GetHitResultUnderCursor(ECC_Visibility, true, traceResult)) return;

	if(!_isQueueing)
	{
		IControllableUnit::Execute_StopMoving(_SelectedUnit);
		IControllableUnit::Execute_SetMoveLocation(_SelectedUnit, traceResult.Location);
	}
	else
	{
		IControllableUnit::Execute_QueueMoveLocation(_SelectedUnit, traceResult.Location);
	}
}

void APC_RTS::StartQueueing(const FInputActionValue& Value)
{
	_isQueueing = true;
}

void APC_RTS::StopQueueing(const FInputActionValue& Value)
{
	_isQueueing = false;
}
