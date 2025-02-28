// https://github.com/hyaniner/UE505ConfigSample


#include "ConfigBase.h"
#include "ConfigTestLog.h"

UE_DISABLE_OPTIMIZATION

void UConfigBase::SetUpObjectName(const FString& InObjectName)
{
	ConfigObjectName = InObjectName;
}

void UConfigBase::Reset()
{
	ValueInObject = -1;
	
	const FString Message = FString::Printf(TEXT("Reset : Object: %s, ObjectValue: %d"), *ConfigObjectName, ValueInObject);
	DisplayMessage(Message);
}

void UConfigBase::SetValues(int32 InNewValue)
{
	ValueInObject = InNewValue;
	const FString Message = FString::Printf(TEXT("Value set: Object: %s, ObjectValue: %d"), *ConfigObjectName, InNewValue);
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
	
	UConfigTestLog* Subsystem = UConfigTestLog::Get();
	Subsystem->DisplayedLog = Subsystem->DisplayedLog + FString(TEXT("\n")) + InMessage;	
	Subsystem->OnUpdateLog.Broadcast(Subsystem->DisplayedLog);
}

void UConfigBase::PrintValueInCDO()
{
	FString MessageToDisplay = FString::Printf(TEXT("MyName: %s, PrintValueInCDO failed. "), *ConfigObjectName);
	
	UClass* MyClass = GetClass();
	if (IsValid(MyClass))
	{
		const UConfigBase* MyClassDefaultObject = MyClass->GetDefaultObject<UConfigBase>();
		if (IsValid(MyClassDefaultObject))
		{
			MessageToDisplay = FString::Printf(TEXT("MyName: %s / MyClass: %s / ValueInCDO: %d "), *ConfigObjectName, *MyClass->GetName(), MyClassDefaultObject->ValueInObject );		
		}	
	} 

	DisplayMessage(MessageToDisplay);	
}

UPluginNameInEnginePluginOne::UPluginNameInEnginePluginOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UPluginNameInEnginePluginOne"));
}

UPluginNameInEnginePluginTwo::UPluginNameInEnginePluginTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UPluginNameInEnginePluginTwo"));
}

UThisConfigInPluginWillFailInEnginePluginOne::UThisConfigInPluginWillFailInEnginePluginOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UThisConfigInPluginWillFailInEnginePluginOne"));
}

UThisConfigInPluginWillFailInEnginePluginTwo::UThisConfigInPluginWillFailInEnginePluginTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UThisConfigInPluginWillFailInEnginePluginTwo"));
}


UE_ENABLE_OPTIMIZATION


