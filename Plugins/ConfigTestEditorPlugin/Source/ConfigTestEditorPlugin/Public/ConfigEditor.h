// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "ConfigBase.h"
#include "UObject/Object.h"
#include "ConfigEditor.generated.h"


/**
 * EditorPerProjectUserSettings will be saved and loaded successfully in most cases even if there is no additional setting.
 */
UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class CONFIGTESTEDITORPLUGIN_API UConfigEditorPerProjectUserSettings : public UConfigBase
{
	GENERATED_BODY()
};
