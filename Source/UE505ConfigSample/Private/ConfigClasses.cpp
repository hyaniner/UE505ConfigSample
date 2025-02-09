// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigClasses.h"

#include "ConfigTestSubsystem.h"

UE_DISABLE_OPTIMIZATION

void UConfigBase::SetUpObjectName(const FString& InObjectName)
{
	ConfigObjectName = InObjectName;
}

void UConfigBase::Reset()
{
	ValueInObject = -1;
	MyStruct = FConfigTest();
	
	const FString Message = FString::Printf(TEXT("Reset : Object: %s, ObjectValue: %d, StructValue %d "), *ConfigObjectName, ValueInObject, MyStruct.ValueInStruct);
	DisplayMessage(Message);
}

void UConfigBase::SetValues(int32 InObjectValue, int32 InStructValue)
{
	ValueInObject = InObjectValue;
	MyStruct.ValueInStruct = InStructValue;
	const FString Message = FString::Printf(TEXT("Value set: Object: %s, ObjectValue: %d, StructValue %d "), *ConfigObjectName, InObjectValue, InStructValue);
	DisplayMessage(Message);
}


void UConfigBase::TrySaveConfig()
{
	const FString Message = FString::Printf(TEXT("TrySaveConfig : %s"), *ConfigObjectName);
	DisplayMessage(Message);
	SaveConfig();
}

void UConfigBase::TryLoadConfig()
{
	const FString Message = FString::Printf(TEXT("TryLoadConfig : %s"), *ConfigObjectName);
	DisplayMessage(Message);	
	LoadConfig();
}

void UConfigBase::DisplayMessage(const FString& InMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InMessage);
	
	UConfigTestSubsystem* Subsystem = UConfigTestSubsystem::Get();
	const FString NewString = Subsystem->DisplayedMessage + FString(TEXT("\n")) + InMessage;	
	Subsystem->OnUpdateMessage.Broadcast(NewString);
}

UMyCustomFileNameBravoOne::UMyCustomFileNameBravoOne()
{
	UE_LOG(LogTemp, Warning, TEXT("생성자!"));
}

UMyCustomFileNameBravoTwo::UMyCustomFileNameBravoTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("생성자!"));
}


UE_ENABLE_OPTIMIZATION



