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

	ConfigObjects = {
		NewObject<UConfigEditorPerProjectUserSettings>(this, FName(TEXT("UConfigEditorPerProjectUserSettings")))
		, NewObject<UConfigEditor>(this, FName(TEXT("UConfigEditor")))
	};

	for (UConfigBase* Config : ConfigObjects)
	{
		Config->SetUp(Config->GetFName().ToString(), 4, 2);
	}

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



