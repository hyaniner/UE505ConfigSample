// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigBase.generated.h"


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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	FString ConfigObjectName { FString(TEXT("NotSet")) };	

	virtual void SetUpObjectName(const FString& InObjectName);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void Reset();
	
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void SetValues(int32 InNewValue);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TrySaveConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TryLoadConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void DisplayMessage(const FString& InMessage);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void PrintValueInCDO();
};

/**
 * This project has a file, "DefaultConfigTestEnginePlugin.ini" in the folder "/Plugins/ConfigTestEnginePlugin/Config/"
 * By the way, the first item in the Hierarchy(FConfigFileHierarchy Hierarchy inside FConfigBranch) that this is belonged to, is the "../../../Engine/Config/PluginBase.ini".
 * And inside the PluginBase.ini, there is an item "bCanSaveAllSections=true" inside the section "[SectionsToSave]".
 * So, when you just add "Default{PluginName}.ini", basically every class will be saved if that class uses this Config file.
 * note: You can override this by adding "bCanSaveAllSections=false" into the "Default{PluginName}.ini".
 * (At now, there is the "bCanSaveAllSections=false" inside "DefaultConfigTestEnginePlugin.ini", but it is commented out.)
 * (Also, I commented out "+Section=/Script/ConfigTestEnginePlugin.PluginNameInEnginePluginOne" now.)
 */
UCLASS(BlueprintType, Blueprintable, Config = ConfigTestEnginePlugin)
class CONFIGTESTENGINEPLUGIN_API UPluginNameInEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UPluginNameInEnginePluginOne();
};

/**
 * See the comment of UPluginNameInEnginePluginOne above.  This is the same case of it.
 */
UCLASS(BlueprintType, Blueprintable, Config = ConfigTestEnginePlugin)
class CONFIGTESTENGINEPLUGIN_API UPluginNameInEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UPluginNameInEnginePluginTwo();
};

/**
 * In "{ProjectFolder}/Config/DefaultEngine.ini", we have an item "
 * +Section=/Script/ConfigTestEnginePlugin.EngineInEnginePluginOne" in the section "[SectionsToSave]".
 * So this will succeed to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = Engine)
class CONFIGTESTENGINEPLUGIN_API UEngineInEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * In "{ProjectFolder}/Config/DefaultEngine.ini", we do NOT have an item
 * "+Section=/Script/ConfigTestEnginePlugin.EngineInEnginePluginTwo" in the section "[SectionsToSave]".
 * So this will fail to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = Engine)
class CONFIGTESTENGINEPLUGIN_API UEngineInEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * In "{ProjectFolder}/Config/DefaultGame.ini", we have an item
 * "+Section=/Script/ConfigTestEnginePlugin.GameInEnginePluginOne" in the section "[SectionsToSave]".
 * So this will succeed to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class CONFIGTESTENGINEPLUGIN_API UGameInEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * In "{ProjectFolder}/Config/DefaultGame.ini", we do NOT have an item
 * "+Section=/Script/ConfigTestEnginePlugin.GameInEnginePluginTwo" in the section "[SectionsToSave]".
 * So this will fail to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class CONFIGTESTENGINEPLUGIN_API UGameInEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This uses the "GameUserSettings". It will always succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = GameUserSettings)
class CONFIGTESTENGINEPLUGIN_API UGameUserSettingsInEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This uses the "GameUserSettings". It will always succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = GameUserSettings)
class CONFIGTESTENGINEPLUGIN_API UGameUserSettingsInEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This class will fail to save the config.
 * Because it is inside the plugin: Without an additional c++ code, You can not use the custom file name of ini inside the plugin.
 * To see details, see: https://hyaniner.com/en/blog/config-ini-of-ue-5.5-20250218/
 */
UCLASS(BlueprintType, Blueprintable, Config = ThisConfigInPluginWillFail)
class CONFIGTESTENGINEPLUGIN_API UThisConfigInPluginWillFailInEnginePluginOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UThisConfigInPluginWillFailInEnginePluginOne();
};

/**
 * See the comment of UThisConfigInPluginWillFailInEnginePluginOne above.  This is the same case of it.
 */
UCLASS(BlueprintType, Blueprintable, Config = ThisConfigInPluginWillFail)
class CONFIGTESTENGINEPLUGIN_API UThisConfigInPluginWillFailInEnginePluginTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UThisConfigInPluginWillFailInEnginePluginTwo();
};

