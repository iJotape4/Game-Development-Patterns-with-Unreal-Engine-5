// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class RTS_AI_API UCommand : public UObject
{
	GENERATED_BODY()
public:
	virtual void Execute();
};
