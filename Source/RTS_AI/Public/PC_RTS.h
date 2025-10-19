#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "PC_RTS.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class RTS_AI_API APC_RTS : public APlayerController
{
	GENERATED_BODY()
public:
	APC_RTS();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AActor> _SelectedUnit;
	UPROPERTY(VisibleInstanceOnly)
	bool _isQueueing;

	// Enhanced Input assets (assign in Blueprint or defaults)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> ActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> QueueAction;

	void Select(const FInputActionValue& Value);
	void ActionReleased(const FInputActionValue& Value);
	void StartQueueing(const FInputActionValue& Value);
	void StopQueueing(const FInputActionValue& Value);
};
