// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "ConfigBase.h"
#include "UObject/Object.h"
#include "ConfigEditor.generated.h"


/**
 * In "{ProjectFolder}/Config/DefaultEditor.ini" (In project folder. Not plugin folder.),
 * we do NOT have an item "+Section=/Script/ConfigTestEditorPlugin.EditorInEditorPlugin" in the section "[SectionsToSave]".
 * (We don't even have a section "[SectionsToSave]" now.)
 * So this will fail to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = Editor)
class CONFIGTESTEDITORPLUGIN_API UEditorInEditorPlugin : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * EditorPerProjectUserSettings will be saved and loaded successfully in most cases even if there is no additional setting.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class CONFIGTESTEDITORPLUGIN_API UEdtPrPrjtUsrSettingsInPlugin : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * String "EditorSettings" contains a string "Editor", and this is not "Editor" at the same time.
 * So this will succeed to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorSettings)
class CONFIGTESTEDITORPLUGIN_API UEditorSettingsInEditorPlugin : public UConfigBase
{
	GENERATED_BODY()
};

/**
 * String "EditorKeyBindings" contains a string "Editor", and this is not "Editor" at the same time.
 * So this will succeed to save.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorKeyBindings)
class CONFIGTESTEDITORPLUGIN_API UEditorKeyBindingsInEditorPlugin : public UConfigBase
{
	GENERATED_BODY()
};


/**
 * This will succeed to save, but this will fail to load.
 * see https://hyaniner.com/en/blog/config-ini-of-ue-5.5-20250218/#editorlayout-is-different
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorLayout)
class CONFIGTESTEDITORPLUGIN_API UEditorLayoutInEditorPlugin : public UConfigBase
{
	GENERATED_BODY()
public:
	UEditorLayoutInEditorPlugin();
};

