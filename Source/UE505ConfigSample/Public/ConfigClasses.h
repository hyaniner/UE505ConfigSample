// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConfigBase.h"
#include "UObject/Object.h"
#include "ConfigClasses.generated.h"




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





