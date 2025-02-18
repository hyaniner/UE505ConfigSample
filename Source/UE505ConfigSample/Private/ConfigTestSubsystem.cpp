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
		NewObject<UConfigTestEnginePluginOne>(this, FName(TEXT("UConfigTestEnginePluginOne")))
		, NewObject<UConfigTestEnginePluginTwo>(this, FName(TEXT("UConfigTestEnginePluginTwo")))
		, NewObject<UThisConfigInPluginWillFailOne>(this, FName(TEXT("UThisConfigInPluginWillFailOne")))
		, NewObject<UThisConfigInPluginWillFailTwo>(this, FName(TEXT("UThisConfigInPluginWillFailTwo")))
		, NewObject<UConfigTestEnginePluginEngine>(this, FName(TEXT("UConfigTestEnginePluginEngine")))
		, NewObject<UConfigTestEnginePluginGame>(this, FName(TEXT("UConfigTestEnginePluginGame")))
		, NewObject<UConfigTestEnginePluginUser>(this, FName(TEXT("UConfigTestEnginePluginUser")))
		, NewObject<UGameInGameModuleOne>(this, FName(TEXT("UGameInGameModuleOne")))
		, NewObject<UGameInGameModuleTwo>(this, FName(TEXT("UGameInGameModuleTwo")))
		, NewObject<UEngineInGameModule>(this, FName(TEXT("UEngineInGameModule")))
		, NewObject<UUserInGameModule>(this, FName(TEXT("UUserInGameModule")))
		, NewObject<UCustomInGameModuleAlphaOne>(this, FName(TEXT("UCustomInGameModuleAlphaOne")))
		, NewObject<UCustomInGameModuleAlphaTwo>(this, FName(TEXT("UCustomInGameModuleAlphaTwo")))
		, NewObject<UCustomInGameModuleBravoOne>(this, FName(TEXT("UCustomInGameModuleBravoOne")))
		, NewObject<UCustomInGameModuleBravoTwo>(this, FName(TEXT("UCustomInGameModuleBravoTwo")))
		, NewObject<UCustomInGameModuleCharlieOne>(this, FName(TEXT("UCustomInGameModuleCharlieOne")))
		, NewObject<UCustomInGameModuleWillBeFail>(this, FName(TEXT("UCustomInGameModuleWillBeFail")))

//Without this preprocessor, packaging will fail.
#if WITH_EDITOR  		
		, NewObject<UConfigEditorPerProjectUserSettings>(this, FName(TEXT("UConfigEditorPerProjectUserSettings")))
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
			Config->ConfigObjectName.Equals(FString(TEXT("UCustomInGameModuleBravoTwo")))
			|| Config->ConfigObjectName.Equals(FString(TEXT("UCustomInGameModuleCharlieOne")))
			|| Config->ConfigObjectName.Equals(FString(TEXT("UCustomInGameModuleWillBeFail")))
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

void UConfigTestSubsystem::ReloadConfigCacheInEngine()
{

	
	TArray<UConfigBase*> CDOs =
		{
			GetMutableDefault<UGameInGameModuleOne>()
			, GetMutableDefault<UGameInGameModuleTwo>()
			, GetMutableDefault<UCustomInGameModuleAlphaOne>()
			, GetMutableDefault<UCustomInGameModuleAlphaTwo>()
			, GetMutableDefault<UCustomInGameModuleBravoOne>()
			, GetMutableDefault<UCustomInGameModuleBravoTwo>()
#if WITH_EDITOR	
			, GetMutableDefault<UConfigEditorPerProjectUserSettings>()
#endif
		};

	/*for (UConfigBase* InItem : CDOs)
	{
		InItem->Reset();
	}*/
	
	TArray<FName> BaseNames =
	{
		FName(TEXT("MyCustomFileNameAlpha"))
		, FName(TEXT("MyCustomFileNameBravo"))
	};

	FConfigCacheIni* ConfigCache = GConfig;

	for (const FName ItemToWork : BaseNames)
	{
		FString FileName = ConfigCache->GetConfigFilename(*(ItemToWork.ToString()));
		FConfigBranch* Branch =	ConfigCache->FindBranchWithNoReload(ItemToWork, FileName);
		//unload를 먼저 해볼까' ㅅ'?
		Branch->SafeUnload();		
		Branch->SafeReload();		
	}
	



}

UE_ENABLE_OPTIMIZATION

