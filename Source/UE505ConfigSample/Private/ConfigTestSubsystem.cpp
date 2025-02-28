// https://github.com/hyaniner/UE505ConfigSample


#include "UE505ConfigSample/Public/ConfigTestSubsystem.h"
#include "ConfigTestLog.h"
#include "UE505ConfigSample/Public/ConfigClasses.h"
#include "UE505ConfigSample/Public/UE505ConfigSample.h"


#if WITH_EDITOR
#include "ConfigEditor.h"
#endif


UE_DISABLE_OPTIMIZATION

UConfigTestSubsystem* UConfigTestSubsystem::Get()
{
	if (GWorld)
	{
		const UGameInstance* GameInstance = GWorld->GetGameInstance();
		return GameInstance->GetSubsystem<UConfigTestSubsystem>();
	}

	return nullptr;	
}

void UConfigTestSubsystem::PostInitProperties()
{
	Super::PostInitProperties();

	if (!IsTemplate())
	{
		UE_LOG(CTestLog, Warning, TEXT("서브시스템 시작"))	
	}
}

void UConfigTestSubsystem::BeginDestroy()
{
	OnClearObject.Clear();
	
	Super::BeginDestroy();
}

void UConfigTestSubsystem::ConstructConfigObjects()
{
	OnClearObject.Broadcast();
	
	ConfigObjects.Reset();

	ConfigObjects = {
		NewObject<UPluginNameInEnginePluginOne>(this, FName(TEXT("UPluginNameInEnginePluginOne")))
		, NewObject<UPluginNameInEnginePluginTwo>(this, FName(TEXT("UPluginNameInEnginePluginTwo")))
		, NewObject<UThisConfigInPluginWillFailInEnginePluginOne>(this, FName(TEXT("UThisConfigInPluginWillFailInEnginePluginOne")))
		, NewObject<UThisConfigInPluginWillFailInEnginePluginTwo>(this, FName(TEXT("UThisConfigInPluginWillFailInEnginePluginTwo")))
		, NewObject<UEngineInEnginePluginOne>(this, FName(TEXT("UEngineInEnginePluginOne")))
		, NewObject<UEngineInEnginePluginTwo>(this, FName(TEXT("UEngineInEnginePluginTwo")))
		, NewObject<UGameInEnginePluginOne>(this, FName(TEXT("UGameInEnginePluginOne")))
		, NewObject<UGameInEnginePluginTwo>(this, FName(TEXT("UGameInEnginePluginTwo")))
		, NewObject<UGameUserSettingsInEnginePluginOne>(this, FName(TEXT("UGameUserSettingsInEnginePluginOne")))
		, NewObject<UGameUserSettingsInEnginePluginTwo>(this, FName(TEXT("UGameUserSettingsInEnginePluginTwo")))
		, NewObject<UGameInGameModuleOne>(this, FName(TEXT("UGameInGameModuleOne")))
		, NewObject<UGameInGameModuleTwo>(this, FName(TEXT("UGameInGameModuleTwo")))
		, NewObject<UEngineInGameModule>(this, FName(TEXT("UEngineInGameModule")))
		, NewObject<UGameUserSettingsInGameModule>(this, FName(TEXT("UGameUserSettingsInGameModule")))
		, NewObject<UCustomInGameModuleAlphaOne>(this, FName(TEXT("UCustomInGameModuleAlphaOne")))
		, NewObject<UCustomInGameModuleAlphaTwo>(this, FName(TEXT("UCustomInGameModuleAlphaTwo")))
		, NewObject<UCustomInGameModuleBravoOne>(this, FName(TEXT("UCustomInGameModuleBravoOne")))
		, NewObject<UCustomInGameModuleBravoTwo>(this, FName(TEXT("UCustomInGameModuleBravoTwo")))
		, NewObject<UCustomInGameModuleCharlieOne>(this, FName(TEXT("UCustomInGameModuleCharlieOne")))
		, NewObject<UCustomInGameModuleWillBeFail>(this, FName(TEXT("UCustomInGameModuleWillBeFail")))
		, NewObject<UCustomButBaseNameHasUser>(this, FName(TEXT("UCustomButBaseNameHasUser")))

//Without this preprocessor, packaging will fail.
#if WITH_EDITOR  		
		, NewObject<UEditorInEditorPlugin>(this, FName(TEXT("UEditorInEditorPlugin")))
		, NewObject<UEditorInGameModule>(this, FName(TEXT("UEditorInGameModule")))		
		, NewObject<UEdtPrPrjtUsrSettingsInPlugin>(this, FName(TEXT("UEdtPrPrjtUsrSettingsInPlugin")))
		, NewObject<UEdtPrPrjtUsrSettingsInGameModule>(this, FName(TEXT("UEdtPrPrjtUsrSettingsInGameModule")))
		, NewObject<UEditorSettingsInEditorPlugin>(this, FName(TEXT("UEditorSettingsInEditorPlugin")))
		, NewObject<UEditorSettingsInGameModule>(this, FName(TEXT("UEditorSettingsInGameModule")))
		, NewObject<UEditorKeyBindingsInEditorPlugin>(this, FName(TEXT("UEditorKeyBindingsInEditorPlugin")))
		, NewObject<UEditorKeyBindingsInGameModule>(this, FName(TEXT("UEditorKeyBindingsInGameModule")))
		, NewObject<UEditorLayoutInEditorPlugin>(this, FName(TEXT("UEditorLayoutInEditorPlugin")))
		, NewObject<UEditorLayoutInGameModule>(this, FName(TEXT("UEditorLayoutInGameModule")))
		, NewObject<UConfigEditorConfigInGameModule>(this, FName(TEXT("UConfigEditorConfigInGameModule")))
#endif
	};

	for (UConfigBase* Config : ConfigObjects)
	{
		Config->SetUpObjectName(Config->GetFName().ToString());
	}
	
	UConfigTestLog::Get()->DisplayedLog = FString(TEXT("Initialized in cpp")); 
	
}

void UConfigTestSubsystem::TryToSaveAll()
{
	for (UConfigBase* Config : ConfigObjects)
	{
		if (
			Config->ConfigObjectName.Equals(FString(TEXT("UEditorLayoutInEditorPlugin")))
			|| Config->ConfigObjectName.Equals(FString(TEXT("UEditorLayoutInGameModule")))
			)
		{
			UE_LOG(LogTemp, Warning, TEXT("BreakPoint!"));			
		}
		
		Config->TrySaveConfig();
	}
}

void UConfigTestSubsystem::TryToLoadAll()
{
	for (UConfigBase* Config : ConfigObjects)
	{
		Config->TryLoadConfig();
	}
}

void UConfigTestSubsystem::CheckAndConvert(const FText& InText, bool& bOutSuccess, int32& OutAsInt32, FString& OutAsString)
{
	bOutSuccess = false;
	OutAsInt32 = INT32_MIN;
	OutAsString = FString(TEXT(""));

	if (InText.IsNumeric())
	{
		int32 AsInt32 = FCString::Atoi(*InText.ToString());
		if (AsInt32 >= 0)
		{
			bOutSuccess = true;		
			OutAsInt32 = AsInt32;	
		}
		else
		{
			OutAsString = FString(TEXT("Value is negative. You can only set the value to -1 with reset."));
		}
	}
	else
	{
		OutAsString = FString(TEXT("Value is not numeric."));	
	}
}

void UConfigTestSubsystem::QuickTestFunction()
{

	UE_LOG(LogTemp, Warning, TEXT("QuickTestFunction Entered!"));


	UClass* WorkingClass = nullptr;
	for (UConfigBase* ConfigItem : ConfigObjects)
	{
		UCustomButBaseNameHasUser* Casted = Cast<UCustomButBaseNameHasUser>(ConfigItem);
		if (IsValid(Casted))
		{
			WorkingClass = Casted->GetClass();			
			break;
		}		
	}

	FString Message = FString(TEXT(""));
	
	if (IsValid(WorkingClass))
	{
		UCustomButBaseNameHasUser* ClassDefaultObjectOfWorkingConfig = WorkingClass->GetDefaultObject<UCustomButBaseNameHasUser>();
		Message = Message + FString(TEXT("\n")) + FString(TEXT("CDO Found."));
		Message = Message + FString(TEXT("\n")) + FString::Printf(TEXT("CDO Name: %s"), *ClassDefaultObjectOfWorkingConfig->ConfigObjectName);

		FString ConfigName = WorkingClass->GetConfigName();
		FString StringFromConfig = FString(TEXT(""));
		
		const bool bSuccess = GConfig->GetString(
			TEXT("/Script/UE505ConfigSample.CustomButBaseNameHasUser")
			, TEXT("ConfigObjectName")
			, StringFromConfig
			, ConfigName
			);
		
		if (bSuccess)
		{
			Message = Message + FString(TEXT("\n")) + FString(TEXT("UCustomButBaseNameHasUser Config Found."));
			Message = Message + FString(TEXT("\n")) + FString::Printf(TEXT("Config String : %s"), *StringFromConfig);
		}
		else
		{
			Message = Message + FString(TEXT("\n")) + FString(TEXT("UCustomButBaseNameHasUser Config NOT Found."));
		}
	}

	
	

	if (!Message.IsEmpty())
	{
		UConfigTestLog* LogSubsystem = UConfigTestLog::Get();
		LogSubsystem->DisplayedLog = LogSubsystem->DisplayedLog + Message;
		LogSubsystem->OnUpdateLog.Broadcast(LogSubsystem->DisplayedLog);	
	}
	
		
#if WITH_EDITOR
	
	if (GConfig)
	{
		FConfigCacheIni* Config = GConfig;
		FConfigBranch* EditorLayoutBranch = Config->FindBranch(FName("EditorLayout"), FString(TEXT("")));
		if (EditorLayoutBranch)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found!"));		
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("EditorLayout Not Found!"));		
		}
	}
	
#else
	
	UE_LOG(LogTemp, Warning, TEXT("We don't have an editor!"));
	
#endif
	
}

UE_ENABLE_OPTIMIZATION

