// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "ConfigBase.h"
#include "UObject/Object.h"
#include "ConfigClasses.generated.h"



/**
 * Classes in the Module
 * - Case of the "Known" category:
 *   - To save the config, You must:
 *	    - Add the "bCanSaveAllSections=true" or add the name of the class in the "SectionsToSave" section!
 *   - "Known" category: Ini file name that provided by the engine. for example, Engine, Game, Input...
 *   - Why?
 *     - The first item of the hierarchy of the "known" ini is "Engine/Config/Base.ini"
 *     - The default value of bCanSaveAllSections in Base.ini is false.
 *     - So if you do not specify the name of the class as the item of the "SectionsToSave", it will fail to save.
 *   - But there are exceptions!
 *     - "GameUserSettings", 
 * - Case of the custom category (= Custom ini file name)
 *   - You must make "Default{CustomFileName}.ini" in the "{ProjectFolder}/Config/" folder.
 *   - Also, you must add "bCanSaveAllSections=true" or add the name of the class in the "SectionsToSave" section.
 *     - Because the ini files inside a module inherits "Engine/Config/Base.ini". The default value of bCanSaveAllSections in Base.ini is false. 
 * Note: You must remove the prefix U from the class name when you add your class name as the item of the "SectionsToSave".
 *   - If you add the prefix U (for example, '(+Section=/Script/UE505ConfigSample.UGameInGameModuleOne)'), it will not work.
 */

/**
 * This will save successfully.
 * We have an item below, inside the "{ProjectFolder}/Config/DefaultGame.ini".
 * (+Section=/Script/UE505ConfigSample.GameInGameModuleOne) 
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class UE505CONFIGSAMPLE_API UGameInGameModuleOne : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This will fail to save,
 * because,
 *   - An item for this class does not exist in the "SectionsToSave" in "{ProjectFolder}/Config/DefaultGame.ini" file.
 *   - Also, "bCanSaveAllSections=true" does not exist in the "SectionsToSave" in "{ProjectFolder}/Config/DefaultGame.ini" file.
 * ---
 * You can manually write the settings for this class in the ini file.
 * Then it will be applied when you run the program.
 * However, if you save the config, the manually written contents will be deleted from ini.
 */
UCLASS(BlueprintType, Blueprintable, Config = Game)
class UE505CONFIGSAMPLE_API UGameInGameModuleTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This will fail to save. There is no item related to this class in the "{ProjectFolder}/Config/DefaultEngine.ini" file.
 */
UCLASS(BlueprintType, Blueprintable, Config = Engine)
class UE505CONFIGSAMPLE_API UEngineInGameModule : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This uses the "GameUserSettings". It will always succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = GameUserSettings)
class UE505CONFIGSAMPLE_API UGameUserSettingsInGameModule : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultCustomInGameModuleAlpha.ini".
 * And this file has "bCanSaveAllSections=true" inside the section '[SectionsToSave]'
 * So if the value of the 'Config' specifier is "CustomInGameModuleAlpha",
 * then all classes will succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleAlpha) //CustomNameInGameAlpha
class UE505CONFIGSAMPLE_API UCustomInGameModuleAlphaOne : public UConfigBase 
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultCustomInGameModuleAlpha.ini".
 * And this file has "bCanSaveAllSections=true" inside the section '[SectionsToSave]'
 * So if the value of the 'Config' specifier is "CustomInGameModuleAlpha",
 * then all classes will succeed in saving.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleAlpha)
class UE505CONFIGSAMPLE_API UCustomInGameModuleAlphaTwo : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * This project has a file, "DefaultCustomInGameModuleBravo.ini".
 * And this file has "+Section=/Script/UE505ConfigSample.CustomInGameModuleBravoOne" inside the section '[SectionsToSave]'
 * So properties with the Config specifier in this class will be saved.
 * Note: You must remove the prefix U from the class name.
 * If you add the prefix U (for example, "+Section=/Script/UE505ConfigSample.UCustomInGameModuleBravoOne"), it will not work.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleBravo)
class UE505CONFIGSAMPLE_API UCustomInGameModuleBravoOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UCustomInGameModuleBravoOne();
};

/**
 * This project has a file, "DefaultCustomInGameModuleBravo.ini".
 * And there is no item related to this class inside the section '[SectionsToSave]'.
 * So properties with the Config specifier in this class will NOT be saved.
 * ---
 * You can manually write the settings for this class in the ini file.
 * Then it will be applied when you run the program.
 * However, if you save the config, the manually written contents will be deleted from ini.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleBravo)
class UE505CONFIGSAMPLE_API UCustomInGameModuleBravoTwo : public UConfigBase
{
	GENERATED_BODY()
public:
	UCustomInGameModuleBravoTwo();
};


/**
 * There is no file with the name, "DefaultCustomInGameModuleCharlie". So it will fail to save the config.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleCharlie)
class UE505CONFIGSAMPLE_API UCustomInGameModuleCharlieOne : public UConfigBase
{
	GENERATED_BODY()
public:
	UCustomInGameModuleCharlieOne();
};

/**
 * There is no file with the name, "DefaultCustomInGameModuleWillBeFail". So it will fail to save the config.
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomInGameModuleWillBeFail)
class UE505CONFIGSAMPLE_API UCustomInGameModuleWillBeFail : public UConfigBase
{
	GENERATED_BODY()
public:
	UCustomInGameModuleWillBeFail();
};

/**
 * String "CustomButBaseNameHasUser" contains a string "User", so this will succeed to save.
 * But, "DefaultCustomButBaseNameHasUser.ini" does not exist in the folder, "{ProjectFolder}/Config/". So it will not be loaded. 
 * And we have some additional story about this.
 * see: https://hyaniner.com/en/blog/config-ini-of-ue-5.5-20250218/#deleting-ini-after-failure-of-loading
 */
UCLASS(BlueprintType, Blueprintable, Config = CustomButBaseNameHasUser)
class UE505CONFIGSAMPLE_API UCustomButBaseNameHasUser : public UConfigBase
{
	GENERATED_BODY()
public:
	UCustomButBaseNameHasUser();
};


/**
 * We can not tell that this is a good practice, but it is for testing of assuming
 * a class within the game module uses "EditorPerProjectUserSettings".
 * 
 * EditorPerProjectUserSettings will be saved and loaded successfully in most cases even if there is no additional setting.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class UE505CONFIGSAMPLE_API UConfigEditorConfigInGameModule : public UConfigBase
{
	GENERATED_BODY()
	
public:

	//Without this preprocessor, packaging will fail. This is the property, so we use "WITH_EDITORONLY_DATA" here.
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConfigSampleAPI", Config)
	int32 SomeProperty = { -2 };
#endif

	//Without this preprocessor, packaging will fail. This is the function, so we use "WITH_EDITOR" here.	
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	void SomeFunction();
#endif
	
};

/**
 * In "{ProjectFolder}/Config/DefaultEditor.ini", we do NOT have an item
 * "+Section=/Script/UE505ConfigSample.EditorInGameModule" in the section "[SectionsToSave]".
 * (We don't even have a section "[SectionsToSave]" now.)
 * So this will fail to save.
 * ---
 * If there are no calls in c++ code, there is no problem compiling without using the preprocessor in a state like this.
 */
UCLASS(BlueprintType, Blueprintable, Config = Editor)
class UE505CONFIGSAMPLE_API UEditorInGameModule : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * EditorPerProjectUserSettings will be saved and loaded successfully in most cases even if there is no additional setting.
 * ---
 * If there are no calls in c++ code, there is no problem compiling without using the preprocessor in a state like this.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class UE505CONFIGSAMPLE_API UEdtPrPrjtUsrSettingsInGameModule : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * String "EditorSettings" contains a string "Editor", and this is not "Editor" at the same time.
 * So this will succeed to save.
 * ---
 * If there are no calls in c++ code, there is no problem compiling without using the preprocessor in a state like this.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorSettings)
class UE505CONFIGSAMPLE_API UEditorSettingsInGameModule : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * String "EditorKeyBindings" contains a string "Editor", and this is not "Editor" at the same time.
 * So this will succeed to save.
 * ---
 * If there are no calls in c++ code, there is no problem compiling without using the preprocessor in a state like this.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorKeyBindings)
class UE505CONFIGSAMPLE_API UEditorKeyBindingsInGameModule : public UConfigBase
{
	GENERATED_BODY()
};


/**
 * This will succeed to save, but this will fail to load.
 * see https://hyaniner.com/en/blog/config-ini-of-ue-5.5-20250218/#editorlayout-is-different
 * ---
 * If there are no calls in c++ code, there is no problem compiling without using the preprocessor in a state like this.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorLayout)
class UE505CONFIGSAMPLE_API UEditorLayoutInGameModule : public UConfigBase
{
	GENERATED_BODY()
};





