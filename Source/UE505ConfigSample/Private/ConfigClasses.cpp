// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigClasses.h"

void UConfigBase::SetUp(const FString& InObjectName, int32 InValueInObject, int32 InValueInStruct)
{
	ConfigObjectName = InObjectName;
	ValueInObject = InValueInObject;
	MyStruct.ValueInStruct = InValueInStruct;
}


void UConfigBase::TrySaveConfig()
{
	UE_LOG(LogTemp, Warning, TEXT("TrySaveConfig : %s"), *ConfigObjectName);
	SaveConfig();
}

void UConfigBase::TryLoadConfig()
{
	UE_LOG(LogTemp, Warning, TEXT("TryLoadConfig : %s"), *ConfigObjectName);
	LoadConfig();
}
