// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigClasses.h"

UConfigBase::UConfigBase()
	: ValueInObject(-1)
	, MyStruct(FConfigTest())
	, ObjectName(FString(TEXT("NotSet")))
{
}

void UConfigBase::SetUp(const FString& InObjectName, int32 InValueInObject, int32 InValueInStruct)
{
	ObjectName = InObjectName;
	ValueInObject = InValueInObject;
	MyStruct.ValueInStruct = InValueInStruct;
}


void UConfigBase::TrySaveConfig()
{
	UE_LOG(LogTemp, Warning, TEXT("TrySaveConfig : %s"), *ObjectName);
	SaveConfig();
}

void UConfigBase::TryLoadConfig()
{
	UE_LOG(LogTemp, Warning, TEXT("TryLoadConfig : %s"), *ObjectName);
	LoadConfig();
}
