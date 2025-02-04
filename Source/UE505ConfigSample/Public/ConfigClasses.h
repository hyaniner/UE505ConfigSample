// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConfigClasses.generated.h"


USTRUCT(BlueprintType)
struct FConfigTest
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 ValueInStruct = { -1 };
};


/**
 * 
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

	virtual void SetUp(const FString& InObjectName, int32 InValueInObject, int32 InValueInStruct);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TrySaveConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	virtual void TryLoadConfig();
};

UCLASS(BlueprintType, Blueprintable, Config = EditorPerProjectUserSettings)
class UE505CONFIGSAMPLE_API UConfigEditorPerProjectUserSettings : public UConfigBase
{
	GENERATED_BODY()
};


UCLASS(BlueprintType, Blueprintable, Config = Editor)
class UE505CONFIGSAMPLE_API UConfigEditor : public UConfigBase
{
	GENERATED_BODY()
};



