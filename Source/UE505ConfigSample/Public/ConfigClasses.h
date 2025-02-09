// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigClasses.generated.h"

/**
 * This does not have the config specifier.
 * But it will have a config specifier in the object below as the property.
 * So it will be saved.
 */
USTRUCT(BlueprintType)
struct FConfigTest
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	int32 ValueInStruct = { -1 };
};


/**
 * This class has a based functionality to save/load config.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class UE505CONFIGSAMPLE_API UConfigBase : public UObject
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
 * EditorPerProjectUserSettings will be saved and loaded successfully in most cases even if there is no additional setting.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class UE505CONFIGSAMPLE_API UConfigEditorPerProjectUserSettings : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This will be saved because there is an item for this class in the "SectionsToSave" in DefaultGame.ini file.
 * (+Section=/Script/UE505ConfigSample.ConfigGameOne)
 * Note: You must remove the prefix U from the class name.
 * If you add the prefix U (for example, '(+Section=/Script/UE505ConfigSample.UConfigGameOne)'), it will not work.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class UE505CONFIGSAMPLE_API UConfigGameOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This will fail to save,
 * because an item for this class does not exist in the "SectionsToSave" in DefaultGame.ini file.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class UE505CONFIGSAMPLE_API UConfigGameTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultMyCustomFileNameAlpha.ini".
 * And this file has "bCanSaveAllSections=true" inside the section '[SectionsToSave]'
 * So if the value of the 'Config' specifier is "MyCustomFileName",
 * then all classes will succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = MyCustomFileNameAlpha)
class UE505CONFIGSAMPLE_API UMyCustomFileNameAlphaOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultMyCustomFileNameAlpha.ini".
 * And this file has "bCanSaveAllSections=true" inside the section '[SectionsToSave]'
 * So if the value of the 'Config' specifier is "MyCustomFileName",
 * then all classes will succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = MyCustomFileNameAlpha)
class UE505CONFIGSAMPLE_API UMyCustomFileNameAlphaTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultMyCustomFileNameBravo.ini".
 * And this file has "+Section=/Script/UE505ConfigSample.MyCustomFileNameBravoOne" inside the section '[SectionsToSave]'
 * So properties with the Config specifier in this class will be saved.
 * Note: You must remove the prefix U from the class name.
 * If you add the prefix U (for example, '(+Section=/Script/UE505ConfigSample.UMyCustomFileNameBravoOne)'), it will not work.
 */
UCLASS(BlueprintType, Blueprintable, Config = MyCustomFileNameBravo)
class UE505CONFIGSAMPLE_API UMyCustomFileNameBravoOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UMyCustomFileNameBravoOne();
};

/**
 * This project has a file, "DefaultMyCustomFileNameBravo.ini".
 * And there is no item related to this class inside the section '[SectionsToSave]'.
 * So properties with the Config specifier in this class will NOT be saved.
 */
UCLASS(BlueprintType, Blueprintable, Config = MyCustomFileNameBravo)
class UE505CONFIGSAMPLE_API UMyCustomFileNameBravoTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UMyCustomFileNameBravoTwo();
};





