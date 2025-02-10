// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigTestSubsystem.h"

#include "ConfigTestLog.h"
#include "UE505ConfigSample/Public/ConfigClasses.h"
#include "UE505ConfigSample/Public/UE505ConfigSample.h"

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
		NewObject<UConfigGameOne>(this, FName(TEXT("UConfigGameOne")))
		, NewObject<UConfigGameTwo>(this, FName(TEXT("UConfigGameTwo")))
		, NewObject<UMyCustomFileNameAlphaOne>(this, FName(TEXT("UMyCustomFileNameAlphaOne")))
		, NewObject<UMyCustomFileNameAlphaTwo>(this, FName(TEXT("UMyCustomFileNameAlphaTwo")))
		, NewObject<UMyCustomFileNameBravoOne>(this, FName(TEXT("UMyCustomFileNameBravoOne")))
		, NewObject<UMyCustomFileNameBravoTwo>(this, FName(TEXT("UMyCustomFileNameBravoTwo")))
#if WITH_EDITOR		
		, NewObject<UConfigEditorPerProjectUserSettings>(this, FName(TEXT("UConfigEditorPerProjectUserSettings")))
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
			GetMutableDefault<UConfigGameOne>()
			, GetMutableDefault<UConfigGameTwo>()
			, GetMutableDefault<UMyCustomFileNameAlphaOne>()
			, GetMutableDefault<UMyCustomFileNameAlphaTwo>()
			, GetMutableDefault<UMyCustomFileNameBravoOne>()
			, GetMutableDefault<UMyCustomFileNameBravoTwo>()
#if WITH_EDITOR	&& !UE_BUILD_SHIPPING
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

