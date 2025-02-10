// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	virtual void Reset();
	
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	virtual void SetValues(int32 InObjectValue, int32 InStructValue);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	virtual void TrySaveConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	virtual void TryLoadConfig();

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI")
	void DisplayMessage(const FString& InMessage);
};



