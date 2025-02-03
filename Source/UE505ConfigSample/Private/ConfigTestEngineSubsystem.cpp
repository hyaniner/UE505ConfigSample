// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigTestEngineSubsystem.h"

#include "UE505ConfigSample/Public/ConfigClasses.h"
#include "UE505ConfigSample/Public/UE505ConfigSample.h"


void UConfigTestEngineSubsystem::PostInitProperties()
{
	Super::PostInitProperties();

	if (!IsTemplate())
	{
		UE_LOG(CTestLog, Warning, TEXT("서브시스템 시작"))	
	}
}

void UConfigTestEngineSubsystem::SetUp()
{
	ConfigObjects.Reset();

	FString ObjectName = FString(TEXT("ConfigEditorPerProjectUserSettings"));
	UConfigBase* Instance = NewObject<UConfigEditorPerProjectUserSettings>(this, FName(ObjectName));
	Instance->SetUp(ObjectName, 2, 3);
	ConfigObjects.Emplace(Instance);
}

void UConfigTestEngineSubsystem::TestConfig(int32 InValueInObject, int32 InValueInStruct)
{	
}

void UConfigTestEngineSubsystem::TryToSaveConfig()
{
	for (UConfigBase* Config : ConfigObjects)
	{
		Config->TrySaveConfig();
	}
}



