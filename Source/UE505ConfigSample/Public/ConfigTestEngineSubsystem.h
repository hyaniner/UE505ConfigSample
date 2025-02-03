// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ConfigTestEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UE505CONFIGSAMPLE_API UConfigTestEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

	virtual void PostInitProperties() override;;
};
