// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE505ConfigSample/Public/UE505ConfigSample.h"

#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(CTestLog);




void FConfigSampleModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("시작!"));
	IModuleInterface::StartupModule();
}

void FConfigSampleModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FConfigSampleModule, UE505ConfigSample, "UE505ConfigSample");

