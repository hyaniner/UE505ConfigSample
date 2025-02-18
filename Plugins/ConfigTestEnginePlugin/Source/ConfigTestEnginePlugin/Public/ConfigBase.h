// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigBase.generated.h"




/**
 * This does not have the config specifier.
 * But it will have a config specifier in the object below as the property.
 * So it will be saved.
 */
USTRUCT(BlueprintType)
struct CONFIGTESTENGINEPLUGIN_API FConfigTest
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	int32 ValueInStruct = { -1 };
};

/**
 * This class has a based functionality to save/load config.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class CONFIGTESTENGINEPLUGIN_API UConfigBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI", Config)
	int32 ValueInObject { -1 };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI", Config)
	FConfigTest MyStruct { FConfigTest() };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI", Config)
	FString ConfigObjectName { FString(TEXT("NotSet")) };	

	virtual void SetUpObjectName(const FString& InObjectName);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void Reset();
	
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void SetValues(int32 InObjectValue, int32 InStructValue);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TrySaveConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TryLoadConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void DisplayMessage(const FString& InMessage);
};

/**
 * This project has a file, "DefaultConfigTestEnginePlugin.ini" in the folder "/Plugins/ConfigTestEnginePlugin/Config/"
 * By the way, the first item in the Hierarchy(FConfigFileHierarchy Hierarchy inside FConfigBranch) that this is belonged to, is the "../../../Engine/Config/PluginBase.ini".
 * And inside the PluginBase.ini, there is an item "bCanSaveAllSections=true" inside the section "[SectionsToSave]".
 * So, when you just add "Default{PluginName}.ini", basically every class will be saved if that class uses this Config file.
 * note: You can override this by adding "bCanSaveAllSections=false" into the "Default{PluginName}.ini".
 * (At now, there is the "bCanSaveAllSections=false" inside "DefaultConfigTestEnginePlugin.ini", but it is commented out.)
 * (Also, I commented out "+Section=/Script/ConfigTestEnginePlugin.ConfigTestEnginePluginOne" now.)
 */
UCLASS(BlueprintType, Blueprintable, Config = ConfigTestEnginePlugin)
class CONFIGTESTENGINEPLUGIN_API UConfigTestEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UConfigTestEnginePluginOne();
};

/**
 * See the comment of UConfigTestEnginePluginOne above.  This is the same case of it.
 */
UCLASS(BlueprintType, Blueprintable, Config = ConfigTestEnginePlugin)
class CONFIGTESTENGINEPLUGIN_API UConfigTestEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UConfigTestEnginePluginTwo();
};

/**
 * This class will fail to save the config.
 * Because it is inside the plugin: Without an additional c++ code, You can not use the custom file name of ini inside the plugin.
 * To see details, see: https://hyaniner.com//en/blog/config-ini-of-ue-5.5-20250218/
 */
UCLASS(BlueprintType, Blueprintable, Config = ThisConfigInPluginWillFail)
class CONFIGTESTENGINEPLUGIN_API UThisConfigInPluginWillFailOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UThisConfigInPluginWillFailOne();
};

/**
 * See the comment of UThisConfigInPluginWillFailOne above.  This is the same case of it.
 */
UCLASS(BlueprintType, Blueprintable, Config = ThisConfigInPluginWillFail)
class CONFIGTESTENGINEPLUGIN_API UThisConfigInPluginWillFailTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UThisConfigInPluginWillFailTwo();
};

