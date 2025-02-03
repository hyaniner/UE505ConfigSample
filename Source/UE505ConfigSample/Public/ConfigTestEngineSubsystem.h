// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ConfigTestEngineSubsystem.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UE505CONFIGSAMPLE_API UConfigTestEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void SetUp();
	
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void TestConfig(int32 InValueInObject, int32 InValueInStruct);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void TryToSaveConfig();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	TArray<TObjectPtr<class UConfigBase>> ConfigObjects;
};
