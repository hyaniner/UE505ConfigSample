// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigBase.h"
#include "ConfigTestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearObject);

/**
 * Subsystems are some kinds of singleton classes of Unreal Engine. They are useful when you need to access something globally.
 * https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-subsystems-in-unreal-engine
 *
 * This is "GameInstanceSubsystem". So it will be constructed whenever the game starts like PIE.
 * I want to note that if this class inherits 'UEngineSubsystem', the value would persist even if PIE is stopped.
 */
UCLASS(Blueprintable, BlueprintType)
class UE505CONFIGSAMPLE_API UConfigTestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	static UConfigTestSubsystem* Get();	
	
	virtual void PostInitProperties() override;

	virtual void BeginDestroy() override;

	/**
	 * - Destruct old ConfigBase objects.
	 * - Construct new ConfigBase objects.
	 * - Write the name of the class for each object.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void ConstructConfigObjects();

	//Try to save all config objects.
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void TryToSaveAll();

	//Try to load all config objects.
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	void TryToLoadAll();

	/**
	 * @brief Try to convert a text input value to an int32 greater than or equal to 0.
	 * If it is not a number or is negative, it outputs an error message specific to that situation.
	 *
	 * @description
	 * Setting to a negative number is only possible by resetting or creating. It's intentional.
	 * This is to distinguish whether the user has changed the value.
	 * 
	 * @param InText - Input value
	 * @param bOutSuccess - Whether converting to an int32 greater than or equal to 0 was successful. 
	 * @param OutAsInt32 - Converted result value.
	 * @param OutAsString - Error message when conversion fails.
	 */
	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	static void CheckAndConvert(const FText& InText, bool& bOutSuccess, int32& OutAsInt32, FString& OutAsString);

	UFUNCTION(BlueprintCallable, Category = "ConfigSampleAPI", meta = (CallInEditor = "true"))
	static void ReloadConfigCacheInEngine();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	TArray<TObjectPtr<class UConfigBase>> ConfigObjects;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "USAPI|GameBoard", meta = (CallInEditor = "true"))
	FOnClearObject OnClearObject;	
};
